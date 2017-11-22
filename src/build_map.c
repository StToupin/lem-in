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

int		add_room(t_lem_in *lem_in, int x, int y, char *line)
{
	int			len;
	t_room		*room;

	len = 0;
	while (line[len] != ' ')
		len++;
	room = room_create(x, y, line, len);
	if (room == NULL)
		return (puterror(lem_in, "(add_room) memory error"));
	return (room_list_push(&(lem_in->rooms), room));
}

int		add_link(t_lem_in *lem_in, char *name_room1, char *name_room2)
{
	t_room	*room1;
	t_room	*room2;

	room1 = find_room(&(lem_in->rooms), name_room1);
	if (room1 == NULL)
		return (puterror(lem_in, "(link) missing first room"));
	room2 = find_room(&(lem_in->rooms), name_room2);
	if (room2 == NULL)
		return (puterror(lem_in, "(link) missing second room"));
	if (room_list_push(&(room1->connected), room2))
		return (puterror(lem_in, "(add_link) memory error 1"));
	if (room_list_push(&(room2->connected), room1))
		return (puterror(lem_in, "(add_link) memory error 2"));
	return (0);
}
