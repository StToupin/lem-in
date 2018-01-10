/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:58:03 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/10 14:58:05 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# define INITIAL_SIZE		(256)
# define MAX_CHAIN_LENGTH	(8)

typedef struct	s_hashmap_elem
{
	char	*key;
	int		in_use;
	void	*data;
}				t_hashmap_elem;

typedef struct	s_hashmap
{
	int				table_size;
	int				size;
	t_hashmap_elem	*data;
}				t_hashmap;

# define MAP_MISSING	-3
# define MAP_FULL		-2
# define MAP_OMEM		-1
# define MAP_OK			0

typedef struct	s_hashmap_env
{
	unsigned long	crc32_tab[256];
}				t_hashmap_env;

/*
** hashmap_init_crc_0.c
*/

void			hashmap_init_crc_000_024(unsigned long *tab);
void			hashmap_init_crc_025_049(unsigned long *tab);
void			hashmap_init_crc_050_074(unsigned long *tab);
void			hashmap_init_crc_075_099(unsigned long *tab);

/*
** hashmap_init_crc_1.c
*/

void			hashmap_init_crc_100_124(unsigned long *tab);
void			hashmap_init_crc_125_149(unsigned long *tab);
void			hashmap_init_crc_150_174(unsigned long *tab);
void			hashmap_init_crc_175_199(unsigned long *tab);

/*
** hashmap_init_crc_2.c
*/

void			hashmap_init_crc_200_224(unsigned long *tab);
void			hashmap_init_crc_225_249(unsigned long *tab);
void			hashmap_init_crc_250_255(unsigned long *tab);

/*
** hashmap_init.c
*/

void			hashmap_init(t_hashmap_env *env);

/*
** hashmap_crc32.c
*/

unsigned int	hashmap_hash_int(t_hashmap_env *env,
								t_hashmap *m,
								char *keystring);

/*
** hashmap.c
*/

t_hashmap		*hashmap_new();
int				hashmap_hash(t_hashmap_env *env, t_hashmap *m, char *key);
int				hashmap_rehash(t_hashmap_env *env, t_hashmap *m);
void			hashmap_free(t_hashmap *m);

/*
** hashmap_op.c
*/

int				hashmap_put(t_hashmap_env *env, t_hashmap *m,
							char *key, void *value);
int				hashmap_get(t_hashmap_env *env, t_hashmap *m,
							char *key, void **arg);
int				hashmap_iterate(t_hashmap *m,
								int (*f)(void *, void*), void *item);
int				hashmap_remove(t_hashmap_env *env, t_hashmap *m, char *key);
int				hashmap_length(t_hashmap *m);

#endif
