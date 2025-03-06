#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
	void	*img;
	int		x;
	int		y;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
	t_data	*img;
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

int	motion(int keycoded, t_vars *vars)
{
	if (keycoded == 119) // w pressed
		vars->img->y -= 5;
	if (keycoded == 115) // s pressed
		vars->img->y += 5;
	if (keycoded == 97) // a pressed
		vars->img->x -= 5;
	if (keycoded == 100) // d pressed
		vars->img->x += 5;
	vars->img->x = vars->img->x % 960;
	vars->img->y = vars->img->y % 540;
	// create_shape(img);
	my_mlx_pixel_put(vars->img, vars->img->x, vars->img->y, 0x00FF0000);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img->img, 0, 0);
	return (0);
}

int	win_close(int keycoded, t_vars *vars)
{
	// printf("%d\n", keycoded);
	// if (keycoded == 98)
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	return (0);
}

int	render_next_frame(t_vars *vars)
{
	printf("%s\n", "called");
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	// mlx_hook(vars->mlx_win, 2, 1L << 0, motion, vars);
	mlx_hook(vars->mlx_win, 2, 1L << 0, win_close, vars);
	return (0);
}

void	mlx_img_init(t_vars *vars)
{
	vars->img = malloc(sizeof(t_data));  // Allocate memory
	if (!vars->img)
		return;
	
	vars->img->img = mlx_new_image(vars->mlx, 960, 540);
	vars->img->addr = mlx_get_data_addr(vars->img->img, &vars->img->bits_per_pixel, 
			&vars->img->line_length, &vars->img->endian);
	vars->img->x = 480;
	vars->img->y = 270;
	my_mlx_pixel_put(vars->img, vars->img->x, vars->img->y, 0x00FF0000);
}

int	main(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 960, 540, "fract-ol");
	mlx_img_init(&vars);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img->img, 0, 0);
	// mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook(vars.mlx_win, 2, 1L << 0, motion, &vars);
	mlx_loop(vars.mlx);
}
