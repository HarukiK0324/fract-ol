/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:40:04 by haruki            #+#    #+#             */
/*   Updated: 2025/03/27 22:10:48 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	ft_print_string(char *c)
{
	if (c == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	return ((int)write(1, c, ft_strlen(c)));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int ft_strlen(char *s)
{
	int i;
	if(s == NULL)
		return (0);
	i = 0;
	while(s[i])
		++i;
	return (i);
}
