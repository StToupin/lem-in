/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 14:51:10 by stoupin           #+#    #+#             */
/*   Updated: 2017/07/19 14:51:11 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem_in.h"

void	init(t_lem_in *lem_in)
{
	room_list_init(&(lem_in->rooms));
	lem_in->start = NULL;
	lem_in->end = NULL;
	room_list_init(&(lem_in->ants));
}

void	clean(t_lem_in *lem_in)
{
	t_room	*room;

	while ((room = room_list_popfront(&(lem_in->rooms))))
	{
		while (room_list_popfront(&(room->connected)))
			;
		free(room);
	}
}

int		add_room(t_lem_in *lem_in, int x, int y, char *line)
{
	int			len;
	t_room		*room;

	len = 0;
	while (line[len] != ' ')
		len++;
	room = room_create(x, y, line, len);
	if (room == NULL)
		return (1);
	return (room_list_push(&(lem_in->rooms), room));
}

int		add_link(t_lem_in *lem_in, char *name_room1, char *name_room2)
{
	t_room	*room1;
	t_room	*room2;

	room1 = find_room(&(lem_in->rooms), name_room1);
	if (room1 == NULL)
		return (1);
	room2 = find_room(&(lem_in->rooms), name_room2);
	if (room2 == NULL)
		return (1);
	if (room_list_push(&(room1->connected), room2))
		return (1);
	if (room_list_push(&(room2->connected), room1))
		return (1);
	return (0);
}
