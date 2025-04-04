/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 02:18:40 by hkasamat          #+#    #+#             */
/*   Updated: 2025/04/04 17:55:52 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

void	draw_mandelbrot(t_data *img, int x, int y)
{
	int	iterations;
	int	max_iterations;

	max_iterations = MAX_ITR + (int)(10 * log10(img->zoom > 1 ? img->zoom : 1));
	img->c_re = 1.5 * (x - win_x / 2.0) / (0.5 * img->zoom * win_x)
		+ img->center_x;
	img->c_im = (y - win_y / 2.0) / (0.5 * img->zoom * win_y) + img->center_y;
	img->z_re = 0;
	img->z_im = 0;
	img->z_re2 = 0;
	img->z_im2 = 0;
	iterations = 0;
	while (img->z_re2 + img->z_im2 <= 4 && iterations < max_iterations)
	{
		img->z_im = 2 * img->z_re * img->z_im + img->c_im;
		img->z_re = img->z_re2 - img->z_im2 + img->c_re;
		img->z_re2 = img->z_re * img->z_re;
		img->z_im2 = img->z_im * img->z_im;
		iterations++;
	}
	my_mlx_pixel_put(img, x, y, get_color(iterations, max_iterations,
			img->color));
}

void	draw_julia(t_data *img, int x, int y)
{
	int	iterations;
	int	max_iterations;

	img->c_re = -0.7;
	img->c_im = 0.27015;
	max_iterations = MAX_ITR + (int)(10 * log10(img->zoom > 1 ? img->zoom : 1));
	img->z_re = 1.5 * (x - win_x / 2.0) / (0.5 * img->zoom * win_x)
		+ img->center_x;
	img->z_im = (y - win_y / 2.0) / (0.5 * img->zoom * win_y) + img->center_y;
	img->z_re2 = img->z_re * img->z_re;
	img->z_im2 = img->z_im * img->z_im;
	iterations = 0;
	while (img->z_re2 + img->z_im2 <= 4 && iterations < max_iterations)
	{
		img->tmp = img->z_re2 - img->z_im2 + img->c_re;
		img->z_im = 2 * img->z_re * img->z_im + img->c_im;
		img->z_re = img->tmp;
		img->z_re2 = img->z_re * img->z_re;
		img->z_im2 = img->z_im * img->z_im;
		iterations++;
	}
	my_mlx_pixel_put(img, x, y, get_color(iterations, max_iterations,
			img->color));
}

void	draw_burning_ship(t_data *img, int x, int y)
{
	int	iterations;
	int	max_iterations;

	max_iterations = MAX_ITR + (int)(10 * log10(img->zoom > 1 ? img->zoom : 1));
	img->c_re = 1.5 * (x - win_x / 2.0) / (0.5 * img->zoom * win_x)
		+ img->center_x;
	img->c_im = (y - win_y / 2.0) / (0.5 * img->zoom * win_y) + img->center_y;
	img->z_re = 0;
	img->z_im = 0;
	img->z_re2 = 0;
	img->z_im2 = 0;
	iterations = 0;
	while (img->z_re2 + img->z_im2 <= 4 && iterations < max_iterations)
	{
		img->z_re = fabs(img->z_re);
		img->z_im = fabs(img->z_im);
		img->tmp = 2 * img->z_re * img->z_im + img->c_im;
		img->z_re = img->z_re2 - img->z_im2 + img->c_re;
		img->z_im = img->tmp;
		img->z_re2 = img->z_re * img->z_re;
		img->z_im2 = img->z_im * img->z_im;
		iterations++;
	}
	my_mlx_pixel_put(img, x, y, get_color(iterations, max_iterations,
			img->color));
}

void	calculate_fractal(t_vars *vars)
{
	int	x;
	int	y;

	mlx_destroy_image(vars->mlx, vars->img->img);
	vars->img->img = mlx_new_image(vars->mlx, win_x, win_y);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
			&vars->img->bits_per_pixel, &vars->img->line_length,
			&vars->img->endian);
	y = 0;
	while (y < win_y)
	{
		x = 0;
		while (x < win_x)
		{
			if (ft_strcmp(vars->fractal_type, "mandelbrot") == 0)
				draw_mandelbrot(vars->img, x, y);
			else if (ft_strcmp(vars->fractal_type, "julia") == 0)
				draw_julia(vars->img, x, y);
			else if (ft_strcmp(vars->fractal_type, "burningship") == 0)
				draw_burning_ship(vars->img, x, y);
			x++;
		}
		y++;
	}
}
