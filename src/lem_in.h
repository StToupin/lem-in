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
	struct s_room_elem	*next;
}				t_room_elem;

typedef struct	s_room_stack
{
	int			n;
	t_room_elem	*top;
}				t_room_stack;

typedef struct	s_room
{
	char			*name;
	int				x;
	int				y;
	t_room_stack	connected;
}				t_room;

typedef struct	s_lem_in
{
	t_room_stack	rooms;
	t_room			*start;
	t_room			*end;
	int				n_ants;
	t_room_stack	ants;
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
void			print_room_stack(t_room_stack *room_stack);

/*
** From room_stack.c
*/

void			room_stack_init(t_room_stack *room_stack);
t_room			*room_create(int x, int y, char *name, int len);
int				room_stack_push(t_room_stack *room_stack, t_room *room);
t_room			*find_room(t_room_stack *room_stack, char *name);
void			print_room(t_room *room);
void			print_room_stack(t_room_stack *room_stack);

/*
** From build_map.c
*/

void			init(t_lem_in *lem_in);
int				add_room(t_lem_in *lem_in, int x, int y, char *line);
int				add_link(t_lem_in *lem_in, char *name_room1, char *name_room2);

/*
** From parse_input.c
*/

int				parse_input(t_lem_in *lem_in);

#endif
