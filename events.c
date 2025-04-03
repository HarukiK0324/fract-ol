/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:25:08 by hkasamat          #+#    #+#             */
/*   Updated: 2025/04/03 15:18:56 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	zoom(int keycode, int x, int y, t_vars *vars)
{
	double	zoom_factor;
	double	mouse_re;
	double	mouse_im;

	mouse_re = 1.5 * (x - win_x / 2) / (0.5 * vars->img->zoom * win_x)
		+ vars->img->center_x;
	mouse_im = (y - win_y / 2) / (0.5 * vars->img->zoom * win_y)
		+ vars->img->center_y;
	if (keycode == ZOOM_IN && vars->img->zoom > 1e14)
		return (0);
	else if (keycode == ZOOM_IN)
		zoom_factor = 1.1;
	else if (keycode == ZOOM_OUT)
		zoom_factor = 0.9;
	else
		return (0);
	vars->img->zoom *= zoom_factor;
	vars->img->center_x = mouse_re - (1.5 * (x - win_x / 2)) / (0.5
			* vars->img->zoom * win_x);
	vars->img->center_y = mouse_im - ((y - win_y / 2)) / (0.5 * vars->img->zoom
			* win_y);
	draw_fractal(vars, vars->fractal_type);
	return (0);
}

int	key_event(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		return (my_mlx_destroy_window(vars), 0);
	else if (keycode >= KEY_LEFT && keycode <= KEY_UP)
		motion(keycode, vars);
	else if (keycode == KEY_L)
		vars->img->color = (vars->img->color + 0x000010) % 0xFFFFFF;
	else if (keycode == KEY_J)
		vars->img->color = (vars->img->color + 0x001000) % 0xFFFFFF;
	else if (keycode == KEY_K)
		vars->img->color = (vars->img->color + 0x100000) % 0xFFFFFF;
	draw_fractal(vars, vars->fractal_type);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img->img, 0, 0);
	return (0);
}

int	my_mlx_destroy_window(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	free(vars->img);
	free(vars->mlx);
	free(vars->fractal_type);
	free(vars);
	exit(EXIT_SUCCESS);
}

void	motion(int keycode, t_vars *vars)
{
	if (keycode == KEY_UP)
		vars->img->center_y -= 0.1 / vars->img->zoom;
	if (keycode == KEY_DOWN)
		vars->img->center_y += 0.1 / vars->img->zoom;
	if (keycode == KEY_LEFT)
		vars->img->center_x -= 0.1 / vars->img->zoom;
	if (keycode == KEY_RIGHT)
		vars->img->center_x += 0.1 / vars->img->zoom;
}
