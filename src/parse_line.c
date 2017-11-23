/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 10:05:34 by stoupin           #+#    #+#             */
/*   Updated: 2017/11/23 10:05:35 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "lem_in.h"

static int	read_number(char *line, int *i, int *result)
{
	int		sign;
	int		ok;
	char	c;

	sign = 1;
	if (line[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	ok = 0;
	*result = 0;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		c = line[*i];
		if ((sign == 1 && *result > (INT_MAX - c + '0') / 10)
			|| (sign == -1 && *result < (INT_MIN + c - '0') / 10))
			return (0);
		*result = (*result * 10) + (c - '0') * sign;
		ok = 1;
		(*i)++;
	}
	return (ok);
}

static int	parse_line_ants(t_lem_in *lem_in, char *line, t_state *state)
{
	int	i;

	i = 0;
	if (!read_number(line, &i, &(lem_in->n_ants)))
		return (puterror(lem_in, "(parse_line_ants) error parsing number"));
	if (line[i] != 0)
		return (puterror(lem_in, "(parse_line_ants) syntax error"));
	if (lem_in->n_ants < 0)
		return (puterror(lem_in, "(parse_line_ants) negative number of ants"));
	*state = S_ROOM;
	return (0);
}

static int	parse_line_room(t_lem_in *lem_in, char *line, t_state *state)
{
	int i;
	int x;
	int y;

	if (*state < S_ROOM || *state > S_STARTEND)
		return (puterror(lem_in, "(parse_line_room) bad state"));
	if (((*state == S_START || *state == S_STARTEND)
			&& lem_in->start != NULL)
		|| ((*state == S_END || *state == S_STARTEND)
			&& lem_in->end != NULL))
		return (puterror(lem_in, "(parse_line_room) two starts or two ends"));
	i = 0;
	while (line[i] != ' ')
		if (line[i++] == '-')
			return (1);
	i++;
	if (!read_number(line, &i, &x) || line[i++] != ' '
		|| !read_number(line, &i, &y) || add_room(lem_in, x, y, line))
		return (1);
	if (*state == S_START || *state == S_STARTEND)
		lem_in->start = lem_in->rooms.last->room;
	if (*state == S_END || *state == S_STARTEND)
		lem_in->end = lem_in->rooms.last->room;
	*state = S_ROOM;
	return (0);
}

static int	parse_line_link(t_lem_in *lem_in, char *line, t_state *state)
{
	int i;
	int dash;

	if (*state != S_ROOM && *state != S_LINK)
		return (puterror(lem_in, "(parse_line_link) bad state"));
	i = 0;
	while (line[i] != '-')
		i++;
	dash = i;
	line[dash] = '\0';
	if (add_link(lem_in, line, line + dash + 1))
		return (1);
	line[dash] = '-';
	*state = S_LINK;
	return (0);
}

int			parse_line(t_lem_in *lem_in, char *line, t_state *state)
{
	int i;
	int n_spaces;
	int n_dashes;

	n_spaces = 0;
	n_dashes = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			n_spaces++;
		else if (line[i] == '-')
			n_dashes++;
		i++;
	}
	if (*state == S_N_ANTS)
		return (parse_line_ants(lem_in, line, state));
	else if (n_spaces == 2)
		return (parse_line_room(lem_in, line, state));
	else if (n_dashes == 1)
		return (parse_line_link(lem_in, line, state));
	return (puterror(lem_in, "(parse_line) syntax error"));
}
