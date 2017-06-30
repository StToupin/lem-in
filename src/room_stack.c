/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 14:26:35 by stoupin           #+#    #+#             */
/*   Updated: 2017/06/29 14:26:36 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft.h"
#include "lem-in.h"

void		room_stack_init(t_room_stack *room_stack)
{
	room_stack->n = 0;
	room_stack->top = NULL;
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
		room->connected = NULL;
	}
	else
	{
		free(room);
		room = NULL;
	}
	return (room);
}

t_room_elem	*room_elem_create(int x, int y, char *name, int len)
{
	t_room		*room;
	t_room_elem *room_elem;
	int			err;

	err = 0;
	room_elem = (t_room_elem*)malloc(sizeof(t_room_elem));
	if (room_elem)
	{
		room = room_create(x, y, name, len);
		if (room)
		{
			room_elem->room = room;
			room_elem->next = NULL;
		}
		else
		{
			free(room_elem);
			room_elem = NULL;
		}
	}
	return (room_elem);
}

int			room_stack_push(t_room_stack *room_stack, t_room_elem *elem)
{
	if (room_stack == NULL || elem == NULL)
		return (1);
	if (room_stack->n == 0)
		room_stack->top = elem;
	else
	{
		elem->next = room_stack->top;
		room_stack->top = elem;
	}
	room_stack->n++;
	return (0);
}

void	print_room(t_room *room)
{
	printf("x: %d, y: %d, name: %s\n", room->x, room->y, room->name);
}

void	print_room_stack(t_room_stack *room_stack)
{
	t_room_elem	*elem;

	elem = room_stack->top;
	while (elem != NULL)
	{
		print_room(elem->room);
		elem = elem->next;
	}
}
