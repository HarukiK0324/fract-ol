/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haruki <haruki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:40:42 by haruki            #+#    #+#             */
/*   Updated: 2025/04/02 03:58:57 by haruki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

#include "minilibx_opengl/mlx.h"
// #include <X11/X.h>
// #include <X11/keysym.h>
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
    double c_re;
    double c_im;
    double z_re;
    double z_im;
    double z_re2;
    double z_im2;
    double tmp;
    u_int32_t color;
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
    COLOR_BLUE = 0x0000FF,
    COLOR_RED = 0xFF0000,
    COLOR_GREEN = 0x00FF00,
    COLOR_PURPLE = 0xFF00FF,
    COLOR_YELLOW = 0xFFFF00,
    COLOR_CYAN = 0x00FFFF,
    COLOR_WHITE = 0xFFFFFF,
    KEY_J = 38,
    KEY_K = 40,
    KEY_L = 37,
    KEY_ESC = 53,
    ZOOM_IN = 4,
    ZOOM_OUT = 5,
    KEY_UP = 126,
    KEY_DOWN = 125,
    KEY_LEFT = 123,
    KEY_RIGHT = 124,
    win_x = 760,
    win_y = 540,
    MAX_ITR = 200
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

#endif 