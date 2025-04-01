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
	vars->img->color = 0x0000FF; // Default color
}

int	get_color(int iterations, int max_iterations, u_int32_t base_color)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iterations == max_iterations)
		return (0);
	t = (double)iterations / max_iterations;
	r = (base_color >> 16) & 0xFF;
	g = (base_color >> 8) & 0xFF;
	b = base_color & 0xFF;
	r = (int)(r * t);
	g = (int)(g * t);
	b = (int)(b * t);
	return ((r << 16) | (g << 8) | b);
}

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
