/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:59:07 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/10 14:59:09 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft.h"
#include "hashmap.h"

static void	hashmap_zero(t_hashmap *m)
{
	int	i;

	i = 0;
	while (i < m->table_size)
	{
		m->data[i].key = NULL;
		m->data[i].in_use = 0;
		m->data[i].data = NULL;
		i++;
	}
}

t_hashmap	*hashmap_new(void)
{
	t_hashmap	*m;

	m = (t_hashmap*)malloc(sizeof(t_hashmap));
	if (m == NULL)
		return (NULL);
	m->data = (t_hashmap_elem*)malloc(sizeof(t_hashmap_elem) * INITIAL_SIZE);
	if (m->data == NULL)
	{
		free(m);
		return (NULL);
	}
	m->table_size = INITIAL_SIZE;
	m->size = 0;
	hashmap_zero(m);
	return (m);
}

/*
** Return the integer of the location in data
** to store the point to the item, or MAP_FULL.
*/

int			hashmap_hash(t_hashmap_env *env, t_hashmap *m, char *key)
{
	int	curr;
	int	i;

	if (m->size >= (m->table_size / 2))
		return (MAP_FULL);
	curr = hashmap_hash_int(env, m, key);
	i = 0;
	while (i < MAX_CHAIN_LENGTH)
	{
		if (m->data[curr].in_use == 0)
			return (curr);
		if (m->data[curr].in_use == 1
			&& (ft_strcmp(m->data[curr].key, key) == 0))
			return (curr);
		curr = (curr + 1) % m->table_size;
		i++;
	}
	return (MAP_FULL);
}

/*
** Doubles the size of the hashmap, and rehashes all the elements
*/

int			hashmap_rehash(t_hashmap_env *env, t_hashmap *m)
{
	int				i;
	t_hashmap_elem	*curr;
	t_hashmap_elem	*temp;
	int				old_size;
	int				status;

	temp = (t_hashmap_elem*)malloc(sizeof(t_hashmap_elem) * 2 * m->table_size);
	if (temp == NULL)
		return (MAP_OMEM);
	curr = m->data;
	m->data = temp;
	old_size = m->table_size;
	m->table_size *= 2;
	m->size = 0;
	hashmap_zero(m);
	i = -1;
	while (++i < old_size)
	{
		if (curr[i].in_use == 0)
			continue ;
		if ((status = hashmap_put(env, m, curr[i].key, curr[i].data)) != MAP_OK)
			return (status);
	}
	free(curr);
	return (MAP_OK);
}

/*
** Deallocate the hashmap
*/

void		hashmap_free(t_hashmap *m)
{
	free(m->data);
	free(m);
}
