/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 14:55:24 by stoupin           #+#    #+#             */
/*   Updated: 2017/07/19 14:55:25 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h> //
#include <stdlib.h> //
#include "lem_in.h"

int			puterror(t_lem_in *lem_in, char *str)
{
	if (lem_in->verbose)
		write_next_line(&(lem_in->output), str);
	return (1);
}

void		print_room(t_lem_in *lem_in, t_room *room)
{
	t_room_elem	*elem;

	if (room == NULL)
		return (write_next_line(&(lem_in->output), "(null)"));
	write_next_str(&(lem_in->output), "x: ");
	write_next_number(&(lem_in->output), room->x);
	write_next_str(&(lem_in->output), ", y: ");
	write_next_number(&(lem_in->output), room->y);
	write_next_str(&(lem_in->output), ", name: ");
	write_next_str(&(lem_in->output), room->name);
	if (room == lem_in->start)
		write_next_str(&(lem_in->output), " (START)");
	if (room == lem_in->end)
		write_next_str(&(lem_in->output), " (END)");
	write_next_byte(&(lem_in->output), '\n');
	elem = room->connected.first;
	while (elem != NULL)
	{
		write_next_str(&(lem_in->output), "  -> ");
		write_next_line(&(lem_in->output), elem->room->name);
		elem = elem->next;
	}
}

void		print_room_list(t_lem_in *lem_in)
{
	t_room_elem	*elem;

	elem = lem_in->rooms.first;
	while (elem != NULL)
	{
		print_room(lem_in, elem->room);
		elem = elem->next;
	}
	write_next_byte(&(lem_in->output), '\n');
}

void		print_path(t_lem_in *lem_in)
{
	t_room	*room;
	int		first;

	write_next_line(&(lem_in->output), "Path found:");
	room = lem_in->start;
	first = 1;
	while (1)
	{
		if (first == 1)
			write_next_str(&(lem_in->output), "  ");
		else
			write_next_str(&(lem_in->output), " -> ");
		first = 0;
		write_next_str(&(lem_in->output), room->name);
		if (room == lem_in->end)
			break;
		room = room->path_next;
	}
	write_next_str(&(lem_in->output), "\n\n");
}
