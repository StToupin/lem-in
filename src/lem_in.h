/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 17:39:59 by stoupin           #+#    #+#             */
/*   Updated: 2017/06/28 17:40:00 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "slist.h"
# include "get_next.h"
# include "hashmap/hashmap.h"

typedef struct	s_room_elem
{
	struct s_room		*room;
	struct s_room_elem	*prev;
	struct s_room_elem	*next;
}				t_room_elem;

typedef struct	s_room_list
{
	int			n;
	t_room_elem	*first;
	t_room_elem	*last;
}				t_room_list;

typedef struct	s_room
{
	char			*name;
	int				x;
	int				y;
	t_room_list		connected;
	struct s_room	*path_prev;
	struct s_room	*path_next;
	int				ant_received;
}				t_room;

typedef struct	s_lem_in
{
	int				verbose;
	t_openfile		input;
	t_slist			input_lines;
	t_openfile		output;
	t_room_list		rooms;
	t_hashmap		*room_hashmap;
	t_room			*start;
	t_room			*end;
	int				n_ants;
	t_room_list		ants;
	t_hashmap_env	hashmap_env;
}				t_lem_in;

typedef enum	e_state
{
	S_N_ANTS,
	S_ROOM,
	S_START,
	S_END,
	S_STARTEND,
	S_LINK
}				t_state;

/*
** From debug.c
*/

int				puterror(t_lem_in *lem_in, char *str);
void			print_room(t_lem_in *lem_in, t_room *room);
void			print_room_list(t_lem_in *lem_in);
void			print_path(t_lem_in *lem_in);

/*
** From room_list.c
*/

void			room_list_init(t_room_list *room_list);
t_room			*room_create(int x, int y, char *name, int len);
int				room_list_push(t_room_list *room_list, t_room *room);
t_room			*room_list_popfront(t_room_list *room_list);

/*
** From build_map.c
*/

int				add_room(t_lem_in *lem_in, int x, int y, char *line);
int				add_link(t_lem_in *lem_in, char *name_room1, char *name_room2);

/*
** From parse_line.c
*/

int				parse_line(t_lem_in *lem_in, char *line, t_state *state);

/*
** From parse_input.c
*/

int				parse_input(t_lem_in *lem_in);

/*
** From solver.c
*/

int				solve_bfs(t_lem_in *lem_in);

/*
** From moove_ants.c
*/

void			move_ants(t_lem_in *lem_in);

#endif
