/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:59:31 by stoupin           #+#    #+#             */
/*   Updated: 2018/01/10 14:59:33 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft.h"
#include "hashmap.h"

/*
** Add a pointer to the hashmap with some key
*/

int	hashmap_put(t_hashmap_env *env, t_hashmap *m, char *key, void *value)
{
	int	index;

	index = hashmap_hash(env, m, key);
	while (index == MAP_FULL)
	{
		if (hashmap_rehash(env, m) == MAP_OMEM)
			return (MAP_OMEM);
		index = hashmap_hash(env, m, key);
	}
	m->data[index].data = value;
	m->data[index].key = key;
	m->data[index].in_use = 1;
	m->size++;
	return (MAP_OK);
}

/*
** Get your pointer out of the hashmap with a key
*/

int	hashmap_get(t_hashmap_env *env, t_hashmap *m, char *key, void **arg)
{
	int	curr;
	int	i;
	int	in_use;

	curr = hashmap_hash_int(env, m, key);
	i = 0;
	while (i < MAX_CHAIN_LENGTH)
	{
		in_use = m->data[curr].in_use;
		if (in_use == 1)
		{
			if (ft_strcmp(m->data[curr].key, key) == 0)
			{
				*arg = m->data[curr].data;
				return (MAP_OK);
			}
		}
		curr = (curr + 1) % m->table_size;
		i++;
	}
	*arg = NULL;
	return (MAP_MISSING);
}

/*
** Iterate the function parameter over each element in the hashmap.  The
** additional any_t argument is passed to the function as its first
** argument and the hashmap element is the second.
*/

int	hashmap_iterate(t_hashmap *m, int (*f)(void *, void*), void *item)
{
	int		i;
	int		status;
	void	*data;

	if (hashmap_length(m) <= 0)
		return (MAP_MISSING);
	i = 0;
	while (i < m->table_size)
	{
		if (m->data[i].in_use != 0)
		{
			data = m->data[i].data;
			status = f(item, data);
			if (status != MAP_OK)
				return (status);
		}
		i++;
	}
	return (MAP_OK);
}

/*
** Remove an element with that key from the map
*/

int	hashmap_remove(t_hashmap_env *env, t_hashmap *m, char *key)
{
	int	i;
	int	curr;
	int	in_use;

	curr = hashmap_hash_int(env, m, key);
	i = 0;
	while (i < MAX_CHAIN_LENGTH)
	{
		in_use = m->data[curr].in_use;
		if (in_use == 1)
		{
			if (ft_strcmp(m->data[curr].key, key) == 0)
			{
				m->data[curr].in_use = 0;
				m->data[curr].data = NULL;
				m->data[curr].key = NULL;
				m->size--;
				return (MAP_OK);
			}
		}
		curr = (curr + 1) % m->table_size;
		i++;
	}
	return (MAP_MISSING);
}

/*
** Return the length of the hashmap
*/

int	hashmap_length(t_hashmap *m)
{
	if (m != NULL)
		return (m->size);
	else
		return (0);
}
