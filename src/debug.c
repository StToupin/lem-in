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
#include "lem_in.h"

static void	print_digit(int n)
{
	char digit;

	if (n == 0)
		return ;
	print_digit(n / 10);
	if (n >= 0)
		digit = ('0' + (n % 10));
	else
		digit = ('0' - (n % 10));
	write(1, &digit, 1);
}

static void	ft_putnbr(int n)
{
	if (n < 0)
		write(1, "-", 1);
	if (n == 0)
		write(1, "0", 1);
	else
		print_digit(n);
}

void		ft_putstr(char *str)
{
	int len;

	len = 0;
	while (str[len] != '\0')
		len++;
	write(1, str, len);
}

void		print_room(t_room *room)
{
	t_room_elem	*elem;

	if (room == NULL)
	{
		ft_putstr("(null)\n");
		return ;
	}
	ft_putstr("x: ");
	ft_putnbr(room->x);
	ft_putstr(", y: ");
	ft_putnbr(room->y);
	ft_putstr(", name: ");
	ft_putstr(room->name);
	ft_putstr("\n");
	elem = room->connected.top;
	while (elem != NULL)
	{
		ft_putstr("  -> ");
		ft_putstr(elem->room->name);
		ft_putstr("\n");
		elem = elem->next;
	}
}

void		print_room_stack(t_room_stack *room_stack)
{
	t_room_elem	*elem;

	elem = room_stack->top;
	while (elem != NULL)
	{
		print_room(elem->room);
		elem = elem->next;
	}
}
