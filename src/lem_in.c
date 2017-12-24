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

static int	init(t_lem_in *lem_in)
{
	lem_in->verbose = 0;
	get_next_init(&(lem_in->input), STDIN_FILENO);
	slist_init(&(lem_in->input_lines));
	get_next_init(&(lem_in->output), 1);
	room_list_init(&(lem_in->rooms));
	lem_in->start = NULL;
	lem_in->end = NULL;
	room_list_init(&(lem_in->ants));
	hashmap_init(&(lem_in->hashmap_env));
	lem_in->room_hashmap = hashmap_new();
	if (lem_in->room_hashmap == NULL)
		return (1);
	return (0);
}

static void	clean(t_lem_in *lem_in)
{
	t_room	*room;

	slist_delete(&(lem_in->input_lines));
	while (room_list_popfront(&(lem_in->ants)))
		;
	while ((room = room_list_popfront(&(lem_in->rooms))))
	{
		while (room_list_popfront(&(room->connected)))
			;
		hashmap_remove(&lem_in->hashmap_env, lem_in->room_hashmap, room->name);
		free(room);
	}
	lem_in->output.eof = 1;
	write_next_byte(&(lem_in->output), 0);
	if (lem_in->room_hashmap != NULL)
		hashmap_free(lem_in->room_hashmap);
}

static void	print_output(t_lem_in *lem_in)
{
	int				i;
	t_slist_elem	*elem;

	i = 0;
	elem = lem_in->input_lines.last;
	while (elem != NULL)
	{
		if (elem->s[0] != '\0')
			write_next_line(&(lem_in->output), elem->s);
		elem = elem->prev;
		i++;
	}
	write_next_byte(&(lem_in->output), '\n');
	move_ants(lem_in);
}

static int	check(t_lem_in *lem_in)
{
	if (lem_in->n_ants == 0)
		return (puterror(lem_in, "no ant"));
	if (lem_in->n_ants < 0)
		return (puterror(lem_in, "negative number of ants"));
	if (lem_in->ants.n != lem_in->n_ants)
		return (puterror(lem_in, "wrong number of ants"));
	if (lem_in->rooms.n == 0)
		return (puterror(lem_in, "no room"));
	if (lem_in->start == NULL)
		return (puterror(lem_in, "undefined start"));
	if (lem_in->end == NULL)
		return (puterror(lem_in, "undefined end"));
	return (0);
}

int			main(int argc, char **argv)
{
	t_lem_in	lem_in;
	int			err;

	err = init(&lem_in);
	lem_in.verbose = (argc > 1 && ft_strcmp(argv[1], "-v") == 0);
	if (err == 0)
	{
		err = parse_input(&lem_in);
		if (lem_in.verbose == 1)
			print_room_list(&lem_in);
		err = check(&lem_in);
	}
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
