/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:40:42 by haruki            #+#    #+#             */
/*   Updated: 2025/03/27 22:14:23 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

#include "minilibx_opengl/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct s_data
{
    void    *img;
    int     x;
    int     y;
    double  zoom;
    double  center_x;
    double  center_y;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}           t_data;

typedef struct s_vars
{
    void    *mlx;
    void    *mlx_win;
    t_data  *img;
    char    *fractal_type;
}           t_vars;

enum {
    KEY_ESC = 53,
    ZOOM_IN = 4,
    ZOOM_OUT = 5,
    KEY_UP = 126,
    KEY_DOWN = 125,
    KEY_LEFT = 123,
    KEY_RIGHT = 124,
    win_x = 540,
    win_y = 540
};

int	ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_strlen(char *s);
int zoom(int keycode, int x, int y, t_vars *vars);
int key_event(int keycode, t_vars *vars);
int my_mlx_destroy_window(t_vars *vars);
void motion(int keycode, t_vars *vars);
void draw_fractal(t_vars *vars, char *fractal);
int	ft_print_string(char *c);
int	ft_strcmp(const char *s1, const char *s2);
int ft_strlen(char *s);

#endif 