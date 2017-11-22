/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:32:17 by stoupin           #+#    #+#             */
/*   Updated: 2017/11/21 15:32:19 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem_in.h"

static void	build_path(t_lem_in *lem_in)
{
	t_room	*room;

	room = lem_in->end;
	room->path_next = room;
	while (room->path_prev != room)
	{
		room->path_prev->path_next = room;
		room = room->path_prev;
	}
}

int			solve_bfs(t_lem_in *lem_in)
{
	t_room_list	queue;
	t_room		*room;
	t_room_elem	*neighbour;

	room_list_init(&queue);
	room_list_push(&queue, lem_in->start);
	lem_in->start->path_prev = lem_in->start;
	while (queue.n > 0)
	{
		room = room_list_popfront(&queue);
		neighbour = room->connected.first;
		while (neighbour != NULL)
		{
			if (neighbour->room->path_prev == NULL)
			{
				room_list_push(&queue, neighbour->room);
				neighbour->room->path_prev = room;
				if (neighbour->room == lem_in->end)
					break ;
			}
			neighbour = neighbour->next;
		}
	}
	if (lem_in->end->path_prev == NULL)
		return (puterror(lem_in, "(solve_bfs) no path to end"));
	build_path(lem_in);
	return (0);
}
