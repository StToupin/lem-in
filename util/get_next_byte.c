/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_byte.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:22:11 by stoupin           #+#    #+#             */
/*   Updated: 2017/05/05 10:23:34 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next.h"

int				get_next_byte(t_openfile *of, char *byte)
{
	if (of == NULL || of->fd < 0 || byte == NULL)
		return (-1);
	if (of->buf_pos == of->buf + of->buf_size)
	{
		of->buf_size = read(of->fd, of->buf, BUFF_SIZE);
		if (of->buf_size == -1)
			return (-1);
		of->buf_pos = of->buf;
		if (of->buf_size == 0)
		{
			of->eof = 1;
			return (0);
		}
	}
	*byte = *(of->buf_pos);
	of->buf_pos++;
	return (1);
}
