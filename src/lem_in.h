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
	struct s_room	*parent;
}				t_room;

typedef struct	s_lem_in
{
	t_room_list		rooms;
	t_room			*start;
	t_room			*end;
	int				n_ants;
	t_room_list		ants;
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

void			ft_putstr(char *str);
void			print_room(t_room *room);
void			print_room_list(t_room_list *room_list);

/*
** From room_list.c
*/

void			room_list_init(t_room_list *room_list);
t_room			*room_create(int x, int y, char *name, int len);
int				room_list_push(t_room_list *room_list, t_room *room);
t_room			*room_list_popfront(t_room_list *room_list);
t_room			*find_room(t_room_list *room_list, char *name);

/*
** From build_map.c
*/

void			init(t_lem_in *lem_in);
void			clean(t_lem_in *lem_in);
int				add_room(t_lem_in *lem_in, int x, int y, char *line);
int				add_link(t_lem_in *lem_in, char *name_room1, char *name_room2);

/*
** From parse_input.c
*/

int				parse_input(t_lem_in *lem_in);

/*
** From solver.c
*/

int				solve_bfs(t_lem_in *lem_in);

#endif
