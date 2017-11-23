/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 17:48:48 by stoupin           #+#    #+#             */
/*   Updated: 2017/06/28 17:48:49 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "lem_in.h"

static int	init_ants(t_lem_in *lem_in)
{
	int	i;

	i = 0;
	while (i < lem_in->n_ants)
	{
		if (room_list_push(&(lem_in->ants), lem_in->start))
			return (puterror(lem_in, "(init_ants) memory error"));
		i++;
	}
	return (0);
}

static int	read_next_line(t_lem_in *lem_in)
{
	int		ret;
	char	*line;

	ret = 0;
	while (ret == 0)
	{
		ret = get_next_line(&(lem_in->input), &line);
		if (ret == 1)
		{
			if (line[0] == '#' && line[1] == '#' && line[2] != '#' &&
			ft_strcmp(line, "##start") != 0 && ft_strcmp(line, "##end") != 0)
				ret = 0;
			else if (line[0] != '\0')
				slist_push_front(&(lem_in->input_lines), line, ft_strlen(line));
			else
			{
				free(line);
				return (1);
			}
			free(line);
		}
		else
			return (puterror(lem_in, "(read_next_line) read error"));
	}
	return (0);
}

int			parse_input(t_lem_in *lem_in)
{
	t_slist_elem	*elem;
	char			*line;
	t_state			s;
	int				error;

	error = 0;
	s = S_N_ANTS;
	while (error == 0 && read_next_line(lem_in) == 0)
	{
		elem = lem_in->input_lines.first;
		line = elem->s;
		if (ft_strcmp(line, "##start") == 0 || ft_strcmp(line, "##end") == 0)
			if (s < S_ROOM || s > S_STARTEND)
				error = puterror(lem_in, "(parse_input) misplaced command");
		if (ft_strcmp(line, "##start") == 0)
			s = (s == S_END || s == S_STARTEND) ? S_STARTEND : S_START;
		else if (ft_strcmp(line, "##end") == 0)
			s = (s == S_START || s == S_STARTEND) ? S_STARTEND : S_END;
		else if (line[0] != '#')
			error = parse_line(lem_in, line, &s);
	}
	if (error)
		line[0] = '\0';
	error |= init_ants(lem_in);
	return (error);
}
