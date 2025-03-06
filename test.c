#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
	void	*img;
	t_vars 	*vars;
	int 	x;
	int 	y;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
	t_data *img;
}			t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// int create_shape(t_data *img)
// {

// }

int motion(int keycoded,t_vars *vars)
{
	if(keycoded == 119) // w pressed
		vars->img->y += 1;
	else if(keycoded == 115) // s pressed
		vars->img->y -= 1;
	else if(keycoded == 97) // a pressed
		vars->img->x -= 1;
	else if(keycoded == 100) // d pressed
		vars->img->x += 1;
	vars->img->x = vars->img->x % 960;
	vars->img->y = vars->img->y % 540;
	t_data *img = mlx_new_image(vars->mlx, 960, 540);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
			&img->endian);
	// create_shape(img);
	my_mlx_pixel_put(img, vars->img->x, vars->img->y, 0x00FF0000);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, img->img, 0, 0);
	vars->img = img;
	return 0;
}

int render_next_frame(t_vars *vars)
{
	mlx_hook(vars->mlx_win, 2, 1L << 0, motion, vars);
	return 0;
}

int	main(void)
{
	t_vars vars;
	t_data img;

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 960, 540, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 960, 540);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	img.x = 0;
	img.y = 0;
	vars.img = &img;
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, img.img, 0, 0);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
}
