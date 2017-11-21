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

void	init(t_lem_in *lem_in)
{
	lem_in->verbose = 0;
	room_list_init(&(lem_in->rooms));
	lem_in->start = NULL;
	lem_in->end = NULL;
	room_list_init(&(lem_in->ants));
}

void	clean(t_lem_in *lem_in)
{
	t_room	*room;
	int		n_links;

	n_links = 0;
	while (room_list_popfront(&(lem_in->ants), "clean ant list pop"))
		;
	while ((room = room_list_popfront(&(lem_in->rooms), "clean room list pop")))
	{
		n_links += room->connected.n;
		while (room_list_popfront(&(room->connected), "clean connected rooms pop"))
			;
		ft_free(room, "clean");
	}
	ft_putnbr(n_links);
	ft_putstr(" links\n");
}

int		add_room(t_lem_in *lem_in, int x, int y, char *line)
{
	int			len;
	t_room		*room;

	len = 0;
	while (line[len] != ' ')
		len++;
	room = room_create(x, y, line, len, "add room create");
	if (room == NULL)
		return (ft_puterror(lem_in->verbose, "(add_room) memory error\n"));
	return (room_list_push(&(lem_in->rooms), room, "add room push"));
}

int		add_link(t_lem_in *lem_in, char *name_room1, char *name_room2)
{
	t_room	*room1;
	t_room	*room2;

	room1 = find_room(&(lem_in->rooms), name_room1);
	if (room1 == NULL)
		return (ft_puterror(lem_in->verbose, "(link) missing first room\n"));
	room2 = find_room(&(lem_in->rooms), name_room2);
	if (room2 == NULL)
		return (ft_puterror(lem_in->verbose, "(link) missing second room\n"));
	if (room_list_push(&(room1->connected), room2, "add link push 1"))
		return (ft_puterror(lem_in->verbose, "(add_link) memory error 1\n"));
	if (room_list_push(&(room2->connected), room1, "add link push 2"))
		return (ft_puterror(lem_in->verbose, "(add_link) memory error 2\n"));
	return (0);
}
