// #include "minilibx-linux/mlx.h"
// #include <stdio.h>
// #include <stdlib.h>

// typedef struct s_data
// {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }			t_data;

// typedef struct s_vars
// {
// 	void	*mlx;
// 	void	*mlx_win;
// }			t_vars;

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

// int	win_close(int keycoded, t_vars *vars)
// {
// 	printf("%d\n", keycoded);
// 	// mlx_destroy_window(vars->mlx, vars->mlx_win);
// 	return (0);
// }

// int	main(void)
// {
// 	t_vars vars;
// 	t_data img;

// 	vars.mlx = mlx_init();
// 	vars.mlx_win = mlx_new_window(vars.mlx, 960, 540, "Hello world!");
// 	mlx_hook(vars.mlx_win, 2, 1L << 0, win_close, &vars);

// 	img.img = mlx_new_image(vars.mlx, 960, 540);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 			&img.endian);
// 	for (int i = 0; i < __INT_MAX__; i++)
// 	{
// 		my_mlx_pixel_put(&img, i % 960, i % 540, 0x00FF0000);
// 	}
// 	mlx_put_image_to_window(vars.mlx, vars.mlx_win, img.img, 0, 0);
// 	mlx_loop(vars.mlx);
// }