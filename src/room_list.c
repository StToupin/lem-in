/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:27:03 by stoupin           #+#    #+#             */
/*   Updated: 2017/11/21 15:27:05 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft.h"
#include "lem_in.h"

void		room_list_init(t_room_list *room_list)
{
	room_list->n = 0;
	room_list->first = NULL;
	room_list->last = NULL;
}

t_room		*room_create(int x, int y, char *name, int len)
{
	t_room		*room;

	room = (t_room*)malloc(sizeof(t_room) + sizeof(char) * (len + 1));
	if (room)
	{
		room->name = (char*)(room) + sizeof(t_room);
		ft_strncpy(room->name, name, len);
		room->x = x;
		room->y = y;
		room_list_init(&(room->connected));
		room->path_prev = NULL;
		room->path_next = NULL;
	}
	return (room);
}

int			room_list_push(t_room_list *room_list, t_room *room)
{
	t_room_elem *elem;

	if (room_list == NULL || room == NULL)
		return (1);
	elem = (t_room_elem*)malloc(sizeof(t_room_elem));
	if (elem == NULL)
		return (1);
	elem->room = room;
	if (room_list->n == 0)
	{
		elem->prev = NULL;
		elem->next = NULL;
		room_list->first = elem;
		room_list->last = elem;
	}
	else
	{
		elem->prev = room_list->last;
		elem->next = NULL;
		room_list->last->next = elem;
		room_list->last = elem;
	}
	room_list->n++;
	return (0);
}

t_room		*room_list_popfront(t_room_list *room_list)
{
	t_room_elem *elem;
	t_room		*room;

	if (room_list->n <= 0)
		return (NULL);
	elem = room_list->first;
	room = elem->room;
	if (elem->next)
		elem->next->prev = NULL;
	room_list->first = elem->next;
	room_list->n--;
	free(elem);
	return (room);
}

t_room		*find_room(t_room_list *room_list, char *name)
{
	t_room_elem	*elem;

	elem = room_list->first;
	while (elem != NULL)
	{
		if (ft_strcmp(elem->room->name, name) == 0)
			return (elem->room);
		elem = elem->next;
	}
	return (NULL);
}
