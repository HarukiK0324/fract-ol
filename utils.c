/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:40:04 by haruki            #+#    #+#             */
/*   Updated: 2025/04/04 17:56:27 by haruki           ###   ########.fr       */
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

int	ft_strlen(char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		++i;
	return (i);
}

int	get_color(int iterations, int max_iterations, u_int32_t base_color)
{
	int	r;
	int	g;
	int	b;

	if (iterations == max_iterations)
		return (0);
	r = (base_color >> 16) & 0xFF;
	g = (base_color >> 8) & 0xFF;
	b = base_color & 0xFF;
	r = (int)(sin(0.1 * iterations + 0) * 127 + 128);
	g = (int)(sin(0.1 * iterations + 2) * 127 + 128);
	b = (int)(sin(0.1 * iterations + 4) * 127 + 128);
	return (base_color + ((r << 16) | (g << 8) | b));
}
