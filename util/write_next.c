/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_next.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:27:03 by stoupin           #+#    #+#             */
/*   Updated: 2017/11/21 15:27:05 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next.h"

void			write_next_byte(t_openfile *of, char byte)
{
	if (of == NULL)
		return ;
	if (of->eof == 1 && of->buf_size > 0)
	{
		write(of->fd, of->buf, of->buf_size);
		return ;
	}
	*(of->buf_pos) = byte;
	of->buf_pos++;
	of->buf_size++;
	if (of->buf_size == BUFF_SIZE)
	{
		write(of->fd, of->buf, of->buf_size);
		of->buf_size = 0;
		of->buf_pos = of->buf;
	}
}

static void		write_next_digit(t_openfile *of, int n)
{
	char digit;

	if (n == 0)
		return ;
	write_next_digit(of, n / 10);
	if (n >= 0)
		digit = ('0' + (n % 10));
	else
		digit = ('0' - (n % 10));
	write_next_byte(of, digit);
}

void			write_next_number(t_openfile *of, int n)
{
	if (n < 0)
		write_next_byte(of, '-');
	if (n == 0)
		write_next_byte(of, '0');
	else
		write_next_digit(of, n);
}

void			write_next_str(t_openfile *of, char *str)
{
	int i;

	if (of == NULL)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		write_next_byte(of, str[i]);
		i++;
	}
}

void			write_next_line(t_openfile *of, char *str)
{
	write_next_str(of, str);
	write_next_byte(of, '\n');
}
