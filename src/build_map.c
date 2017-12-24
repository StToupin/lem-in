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
#include "ft.h"

int		check_room(t_lem_in *lem_in, char *name)
{
	t_room		*room;

	if (name[0] == 'L')
		return (puterror(lem_in, "(add_room) illegal room name"));
	hashmap_get(&lem_in->hashmap_env, lem_in->room_hashmap,
				name, (void*)&room);
	if (room != NULL)
		return (puterror(lem_in, "(add_room) duplicate room name"));
	return (0);
}

int		add_room(t_lem_in *lem_in, int x, int y, char *line)
{
	int			len;
	int			ret;
	t_room		*room;

	len = 0;
	while (line[len] != ' ')
		len++;
	if (len == 0)
		return (puterror(lem_in, "(add_room) empty room name"));
	line[len] = '\0';
	if (check_room(lem_in, line) == 1)
		return (1);
	line[len] = ' ';
	room = room_create(x, y, line, len);
	if (room == NULL || room_list_push(&(lem_in->rooms), room))
		return (puterror(lem_in, "(add_room) memory error"));
	ret = hashmap_put(&lem_in->hashmap_env, lem_in->room_hashmap,
					  room->name, room);
	if (ret != MAP_OK)
		return (1);
	return (0);
}

int		check_link(t_lem_in *lem_in, t_room *room1, t_room *room2)
{
	t_room_elem	*elem;

	if (room1 == room2)
		return (puterror(lem_in, "(add_link) link room to itself"));
	elem = room1->connected.first;
	while (elem != NULL)
	{
		if (elem->room == room2)
			return (puterror(lem_in, "(add_link) duplicate link"));
		elem = elem->next;
	}
	return (0);
}

int		add_link(t_lem_in *lem_in, char *name_room1, char *name_room2)
{
	t_room	*room1;
	t_room	*room2;

	hashmap_get(&lem_in->hashmap_env, lem_in->room_hashmap,
				name_room1, (void*)&room1);
	if (room1 == NULL)
		return (puterror(lem_in, "(link) missing first room"));
	hashmap_get(&lem_in->hashmap_env, lem_in->room_hashmap,
				name_room2, (void*)&room2);
	if (room2 == NULL)
		return (puterror(lem_in, "(link) missing second room"));
	if (check_link(lem_in, room1, room2))
		return (1);
	if (room_list_push(&(room1->connected), room2))
		return (puterror(lem_in, "(add_link) memory error 1"));
	if (room_list_push(&(room2->connected), room1))
		return (puterror(lem_in, "(add_link) memory error 2"));
	return (0);
}
