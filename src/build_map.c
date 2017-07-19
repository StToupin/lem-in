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
	room_stack_init(&(lem_in->rooms));
	lem_in->start = NULL;
	lem_in->end = NULL;
	room_stack_init(&(lem_in->ants));
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
	return (room_stack_push(&(lem_in->rooms), room));
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
	if (room_stack_push(&(room1->connected), room2))
		return (1);
	if (room_stack_push(&(room2->connected), room1))
		return (1);
	return (0);
}
