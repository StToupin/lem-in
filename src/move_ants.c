/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:27:03 by stoupin           #+#    #+#             */
/*   Updated: 2017/11/21 15:27:05 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	init_step(t_lem_in *lem_in)
{
	t_room *room;

	room = lem_in->start;
	while (room != NULL)
	{
		room->ant_received = 0;
		room = room->path_next;
	}
}

static void	print_move(t_lem_in *lem_in, int ant_number, char *room_name,
						int first_move)
{
	if (first_move == 0)
		write_next_byte(&(lem_in->output), ' ');
	write_next_byte(&(lem_in->output), 'L');
	write_next_number(&(lem_in->output), ant_number);
	write_next_byte(&(lem_in->output), '-');
	write_next_str(&(lem_in->output), room_name);
}

static void	move_ant(t_lem_in *lem_in, int ant_number, t_room_elem *ant,
						int first_move)
{
	ant->room = ant->room->path_next;
	ant->room->ant_received = 1;
	print_move(lem_in, ant_number, ant->room->name, first_move);
}

static int	step(t_lem_in *lem_in)
{
	int			ant_number;
	int			first_move;
	int			all_ants_at_the_end;
	t_room_elem *ant;

	init_step(lem_in);
	all_ants_at_the_end = 1;
	ant = lem_in->ants.first;
	ant_number = 1;
	first_move = 1;
	while (ant != NULL)
	{
		if (ant->room != lem_in->end)
		{
			all_ants_at_the_end = 0;
			if (ant->room->path_next->ant_received == 0)
			{
				move_ant(lem_in, ant_number, ant, first_move);
				first_move = 0;
			}
		}
		ant = ant->next;
		ant_number++;
	}
	return (all_ants_at_the_end);
}

void		move_ants(t_lem_in *lem_in)
{
	int all_ants_at_the_end;

	while (1)
	{
		all_ants_at_the_end = step(lem_in);
		if (all_ants_at_the_end == 1)
			break ;
		write_next_byte(&(lem_in->output), '\n');
	}
}
