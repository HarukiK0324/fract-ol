#include "fract-ol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	mlx_img_init(t_vars *vars)
{
	vars->img = malloc(sizeof(t_data));
	if (!vars->img)
		return ;
	vars->img->img = mlx_new_image(vars->mlx, win_x, win_y);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
			&vars->img->bits_per_pixel, &vars->img->line_length,
			&vars->img->endian);
	vars->img->x = win_x / 2;
	vars->img->y = win_y / 2;
	vars->img->zoom = 1.0;
	vars->img->center_x = 0;
	vars->img->center_y = 0;
	vars->img->color = COLOR_BLUE;
}

void	draw_fractal(t_vars *vars, char *fractal)
{
	if (ft_strcmp(fractal, "mandelbrot") == 0 || ft_strcmp(fractal,
			"julia") == 0 || ft_strcmp(fractal, "burningship") == 0)
	{
		vars->fractal_type = fractal;
		calculate_fractal(vars);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img->img, 0, 0);
	}
	else
	{
		my_mlx_destroy_window(vars);
		printf("Usage: ./fractol [mandelbrot/julia/burningship]\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (argc != 2)
	{
		printf("Usage: ./fractol [mandelbrot/julia/burningship]\n");
		exit(EXIT_FAILURE);
	}
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, win_x, win_y, "Fractal Renderer");
	mlx_img_init(&vars);
	draw_fractal(&vars, argv[1]);
	mlx_hook(vars.mlx_win, 2, 0, key_event, &vars);
	mlx_mouse_hook(vars.mlx_win, zoom, &vars);
	mlx_hook(vars.mlx_win, 17, 0, my_mlx_destroy_window, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
