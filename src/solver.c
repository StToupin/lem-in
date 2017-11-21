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

int	solve_bfs(t_lem_in *lem_in)
{
	t_room_list	queue;
	t_room		*room;
	t_room_elem	*neighbour;

	room_list_init(&queue);
	room_list_push(&queue, lem_in->start, "solve_bfs push start room to queue");
	lem_in->start->parent = lem_in->start;
	while (queue.n > 0)
	{
		room = room_list_popfront(&queue, "solve_bfs pop room from queue");
		neighbour = room->connected.first;
		while (neighbour != NULL)
		{
			if (neighbour->room->parent == NULL)
			{
				room_list_push(&queue, neighbour->room, "solve_bfs push room to queue");
				neighbour->room->parent = room;
				if (neighbour->room == lem_in->end)
					break ;
			}
			neighbour = neighbour->next;
		}
	}
	return (lem_in->end->parent == NULL);
}
