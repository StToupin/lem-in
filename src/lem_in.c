/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:27:03 by stoupin           #+#    #+#             */
/*   Updated: 2017/11/21 15:27:05 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "lem_in.h"
#include "slist.h"
#include "get_next.h"
#include "ft.h"

static void	init(t_lem_in *lem_in)
{
	lem_in->verbose = 0;
	slist_init(&(lem_in->input));
	get_next_init(&(lem_in->output), 1);
	room_list_init(&(lem_in->rooms));
	lem_in->start = NULL;
	lem_in->end = NULL;
	room_list_init(&(lem_in->ants));
}

static void	clean(t_lem_in *lem_in)
{
	t_room	*room;

	slist_delete(&(lem_in->input));
	while (room_list_popfront(&(lem_in->ants)))
		;
	while ((room = room_list_popfront(&(lem_in->rooms))))
	{
		while (room_list_popfront(&(room->connected)))
			;
		free(room);
	}
	lem_in->output.eof = 1;
	write_next_byte(&(lem_in->output), 0);
}

static void	print_output(t_lem_in *lem_in)
{
	t_slist_elem	*elem;

	elem = lem_in->input.last;
	while (elem != NULL)
	{
		write_next_line(&(lem_in->output), elem->s);
		elem = elem->prev;
	}
	write_next_byte(&(lem_in->output), '\n');
	move_ants(lem_in);
}

int	main(int argc, char **argv)
{
	t_lem_in	lem_in;
	int			err;

	init(&lem_in);
	lem_in.verbose = (argc > 1 && ft_strcmp(argv[1], "-v") == 0);
	err = get_all_lines(STDIN_FILENO, &(lem_in.input));
	if (err == 0)
		err = parse_input(&lem_in);
	if (err == 0 && lem_in.verbose == 1)
		print_room_list(&lem_in);
	if (err == 0)
		err = solve_bfs(&lem_in);
	if (err == 0 && lem_in.verbose == 1)
		print_path(&lem_in);
	if (err == 0)
 		print_output(&lem_in);
	if (err == 1)
		write_next_line(&(lem_in.output), "ERROR");
	clean(&lem_in);
}
