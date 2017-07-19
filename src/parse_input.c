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

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "lem_in.h"
#include "get_next.h"
#include "ft.h"

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

static int	parse_line_room(t_lem_in *lem_in, char *line, int *state)
{
	int i;
	int x;
	int y;

	if (*state != 0 && *state != 1 && *state != 2)
		return (1);
	if ((*state == 1 && lem_in->start != NULL)
		|| (*state == 2 && lem_in->end != NULL))
		return (1);
	i = 0;
	while (line[i] != ' ')
		if (line[i++] == '-')
			return (1);
	i++;
	if (!read_number(line, &i, &x) || line[i++] != ' '
		|| !read_number(line, &i, &y) || add_room(lem_in, x, y, line))
		return (1);
	if (*state == 1)
		lem_in->start = lem_in->rooms.top->room;
	if (*state == 2)
		lem_in->end = lem_in->rooms.top->room;
	*state = 0;
	return (0);
}

static int	parse_line_link(t_lem_in *lem_in, char *line, int *state)
{
	int i;
	int dash;

	if (*state != 0 && *state != 3)
		return (1);
	i = 0;
	while (line[i] != '-')
		i++;
	dash = i;
	line[dash] = '\0';
	if (add_link(lem_in, line, line + dash + 1))
		return (1);
	*state = 3;
	return (0);
}

static int	parse_line(t_lem_in *lem_in, char *line, int *state)
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
	if (n_spaces == 2)
		return (parse_line_room(lem_in, line, state));
	else if (n_dashes == 1)
		return (parse_line_link(lem_in, line, state));
	return (1);
}

int			parse_input(t_lem_in *lem_in)
{
	t_openfile	of;
	char		*line;
	int			state;
	int			error;

	error = 0;
	state = 0;
	get_next_init(&of, STDIN_FILENO);
	while (get_next_line(&of, &line) == 1 && error == 0)
	{
		if (ft_strcmp(line, "##start") == 0)
			if (state == 0)
				state = 1;
			else
				error = 1;
		else if (ft_strcmp(line, "##end") == 0)
			if (state == 0)
				state = 2;
			else
				error = 1;
		else if (line[0] != '#')
			error = parse_line(lem_in, line, &state);
		free(line);
	}
	return (error);
}
