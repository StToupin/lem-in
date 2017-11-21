/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 13:59:49 by stoupin           #+#    #+#             */
/*   Updated: 2017/06/29 13:59:50 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;
	int				i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		c1 = (unsigned char)s1[i];
		c2 = (unsigned char)s2[i];
		if (c1 != c2)
			return (c1 - c2);
		i++;
	}
	c1 = (unsigned char)s1[i];
	c2 = (unsigned char)s2[i];
	return (c1 - c2);
}

char	*ft_strndup(char *str, int n)
{
	char	*new_str;
	int		i;

	new_str = (char*)ft_malloc(sizeof(char) * (n + 1), "strndup");
	if (new_str != NULL)
	{
		i = 0;
		while (i < n)
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = '\0';
	}
	return (new_str);
}

void	ft_strncpy(char *dest, char *src, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void		*ft_malloc(size_t size, char *dbg_msg)
{
	void	*ptr;

	ptr = malloc(size);
	//printf("malloc %p (%s)\n", ptr, dbg_msg); //
	return (ptr);
}

void		ft_free(void *ptr, char *dbg_msg)
{
	//printf("free %p (%s)\n", ptr, dbg_msg); //
	free(ptr);
}
