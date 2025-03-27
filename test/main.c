#include "fract-ol.h"

typedef struct s_data
{
	void	*img;
	int		x;
	int		y;
	double zoom;
	double center_x;
	double center_y;
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

enum {
    KEY_ESC = 53,
	ZOOM_IN = 4,
	ZOOM_OUT = 5,
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	win_x = 960,
	win_y = 540
};

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	mlx_img_init(t_vars *vars)
{
	vars->img = malloc(sizeof(t_data)); // Allocate memory
	if (!vars->img)
		return ;
	vars->img->img = mlx_new_image(vars->mlx, 960, 540);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
			&vars->img->bits_per_pixel, &vars->img->line_length,
			&vars->img->endian);
	vars->img->x = 480;
	vars->img->y = 270;
	my_mlx_pixel_put(vars->img, vars->img->x, vars->img->y, 0x00FF0000);
}

int my_mlx_destroy_window(t_vars *vars)
{
    mlx_destroy_image(vars->mlx, vars->img->img);
    free(vars->img);
    exit(EXIT_SUCCESS);
}

void motion(int keycode,t_vars *vars)
{
	if(keycode == KEY_UP)
		vars->img->y -= 5;
	if(keycode == KEY_DOWN)
		vars->img->y += 5;
	if(keycode == KEY_LEFT)
		vars->img->x -= 5;
	if(keycode == KEY_RIGHT)
		vars->img->x += 5;
}

int key_event(int keycode,t_vars *vars)
{
	if(keycode == KEY_ESC)
		my_mlx_destroy_window(vars);
	else if(keycode >= KEY_LEFT && keycode <= KEY_UP)
		motion(keycode,vars);
	return (0);
}

void draw_mandelbrot(t_vars *vars,int x,int y)
{
	double c_re;
	double c_im;
	double z_re;
	double z_im;
	double z_re2;
	double z_im2;
	int i;

	c_re = 1.5 * (x - win_x / 2) / (0.5 * vars->img->zoom * win_x) + vars->img->center_x;
	c_im = (y - win_y / 2) / (0.5 * vars->img->zoom * win_y) + vars->img->center_y;
	z_re = 0;
	z_im = 0;
	z_re2 = 0;
	z_im2 = 0;
	i = 0;
	while(z_re * z_re + z_im2 <= 4 && i < 256)
	{
		z_im = 2 * z_re * z_im + c_im;
		z_re = z_re2 - z_im2 + c_re;
		z_re2 = z_re * z_re;
		z_im2 = z_im * z_im;
		i++;
	}
	my_mlx_pixel_put(vars->img,x,y,i * 256);
}

void calculate_mandelbrot(t_vars *vars)
{
	int x;
	int y;

	x = 0;
	while(x < win_x)
	{
		y = 0;
		while(y < win_y)
		{
			draw_mandelbrot(vars,x,y);
			y++;
		}
		x++;
	}
}

void calculate_julia()
{

}

void calculate_burningship()
{

}

void draw_fractal(t_vars *vars, char *fractal)
{
	if (ft_strncmp(fractal,"mandelbrot",11))
		calculate_mandelbrot(vars);
	else if (ft_strncmp(fractal,"julia",6))
		calculate_mandelbrot(vars);
	else if (ft_strncmp(fractal,"burningship",12))
		calculate_mandelbrot(vars);
	else
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		printf("Usage: ./fractol [mandelbrot/julia/burningship]\n");
		exit(EXIT_FAILURE);
	}
}

int zoom(int keycode, t_vars *vars)
{
    int x;
	int y;
    double zoom_factor;

    mlx_mouse_get_pos(vars->mlx_win, &x, &y);
    if (keycode == ZOOM_IN)
        zoom_factor = 1.1;
    else if (keycode == ZOOM_OUT)
        zoom_factor = 0.9;
	else
		return (0);
    vars->img->zoom *= zoom_factor;
    vars->img->center_x += (x - vars->img->center_x) / vars->img->zoom * (1 - zoom_factor);
    vars->img->center_y += (y - vars->img->center_y) / vars->img->zoom * (1 - zoom_factor);
    return (0);
}

int	main(int argc,char *argv[])
{
    t_vars	vars;
    
	if(argc != 2)
	{
		printf("Usage: ./fractol [mandelbrot/julia/burningship]\n");
		exit(EXIT_FAILURE);
	}
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, win_x, win_y, "fract-ol");
	mlx_img_init(&vars);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img->img, 0, 0);
	// draw_fractal(&vars,argv[1]);
	// mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	// mlx_hook(vars.mlx_win, 2, 0, key_event, &vars);
	// mlx_mouse_hook(vars.mlx_win,zoom,&vars);
	// mlx_hook(vars.mlx_win, 17, 0, my_mlx_destroy_window, &vars);
	int x = 0;
	int y =0;
	while(x < win_x)
	{
		y = 0;
		while(y < win_y)
		{
			my_mlx_pixel_put(vars.img,x,y,0x00FF0000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img->img, 0, 0);
	mlx_loop(vars.mlx);
}
