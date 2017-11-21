/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 14:00:46 by stoupin           #+#    #+#             */
/*   Updated: 2017/06/29 14:00:47 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(char *str, int n);
void	ft_strncpy(char *dest, char *src, int len);
void	*ft_malloc(size_t size, char *dbg_msg);
void	ft_free(void *ptr, char *dbg_msg);

#endif
