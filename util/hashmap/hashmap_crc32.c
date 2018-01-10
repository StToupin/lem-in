/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_crc32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:59:11 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/10 14:59:13 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

/*
** Return a 32-bit CRC of the contents of the buffer.
*/

static unsigned long	crc32(t_hashmap_env *env,
								const unsigned char *s)
{
	unsigned int	i;
	unsigned long	crc32val;

	crc32val = 0;
	i = 0;
	while (s[i] != '\0')
	{
		crc32val = env->crc32_tab[(crc32val ^ s[i]) & 0xff] ^ (crc32val >> 8);
		i++;
	}
	return (crc32val);
}

/*
** Hashing function for a string
** using Robert Jenkins' 32 bit Mix Function
** and Knuth's Multiplicative Method
*/

unsigned int			hashmap_hash_int(t_hashmap_env *env,
									t_hashmap *m,
									char *keystring)
{
	unsigned long key;

	key = crc32(env, (unsigned char*)(keystring));
	key += (key << 12);
	key ^= (key >> 22);
	key += (key << 4);
	key ^= (key >> 9);
	key += (key << 10);
	key ^= (key >> 2);
	key += (key << 7);
	key ^= (key >> 12);
	key = (key >> 3) * 2654435761;
	return (key % m->table_size);
}
