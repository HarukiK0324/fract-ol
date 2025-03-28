#include "fract-ol.h"

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    mlx_img_init(t_vars *vars)
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
}


void draw_mandelbrot(t_vars *vars, int x, int y)
{
    double c_re, c_im, z_re, z_im, z_re2, z_im2;
    int i, max_iter = 256;

    c_re = 1.5 * (x - win_x / 2) / (0.5 * vars->img->zoom * win_x) + vars->img->center_x;
    c_im = (y - win_y / 2) / (0.5 * vars->img->zoom * win_y) + vars->img->center_y;
    z_re = z_im = 0;
    z_re2 = z_im2 = 0;
    i = 0;

    while (z_re2 + z_im2 <= 4 && i < max_iter)
    {
        z_im = 2 * z_re * z_im + c_im;
        z_re = z_re2 - z_im2 + c_re;
        z_re2 = z_re * z_re;
        z_im2 = z_im * z_im;
        i++;
    }

    int color = (i == max_iter) ? 0 : i * 0x1000000 / max_iter;
    my_mlx_pixel_put(vars->img, x, y, color);
}

void draw_julia(t_vars *vars, int x, int y)
{
    double c_re = -0.7, c_im = 0.27015; // Fixed Julia set constant
    double z_re, z_im, z_re2, z_im2;
    int i, max_iter = 256;

    z_re = 1.5 * (x - win_x / 2) / (0.5 * vars->img->zoom * win_x) + vars->img->center_x;
    z_im = (y - win_y / 2) / (0.5 * vars->img->zoom * win_y) + vars->img->center_y;
    z_re2 = z_re * z_re;
    z_im2 = z_im * z_im;
    i = 0;

    while (z_re2 + z_im2 <= 4 && i < max_iter)
    {
        double temp = z_re2 - z_im2 + c_re;
        z_im = 2 * z_re * z_im + c_im;
        z_re = temp;
        z_re2 = z_re * z_re;
        z_im2 = z_im * z_im;
        i++;
    }

    int color = (i == max_iter) ? 0 : i * 0x1000000 / max_iter;
    my_mlx_pixel_put(vars->img, x, y, color);
}

void draw_burning_ship(t_vars *vars, int x, int y)
{
    double c_re, c_im, z_re, z_im, z_re2, z_im2;
    int i, max_iter = 256;

    c_re = 1.5 * (x - win_x / 2) / (0.5 * vars->img->zoom * win_x) + vars->img->center_x;
    c_im = (y - win_y / 2) / (0.5 * vars->img->zoom * win_y) + vars->img->center_y;
    z_re = z_im = 0;
    z_re2 = z_im2 = 0;
    i = 0;

    while (z_re2 + z_im2 <= 4 && i < max_iter)
    {
        z_re = fabs(z_re);
        z_im = fabs(z_im);
        double temp = 2 * z_re * z_im + c_im;
        z_re = z_re2 - z_im2 + c_re;
        z_im = temp;
        z_re2 = z_re * z_re;
        z_im2 = z_im * z_im;
        i++;
    }

    int color = (i == max_iter) ? 0 : i * 0x1000000 / max_iter;
    my_mlx_pixel_put(vars->img, x, y, color);
}

void calculate_fractal(t_vars *vars)
{
    int x, y;
    mlx_destroy_image(vars->mlx, vars->img->img);
    mlx_img_init(vars);

    for (x = 0; x < win_x; x++)
    {
        for (y = 0; y < win_y; y++)
        {
            if (ft_strcmp(vars->fractal_type, "mandelbrot") == 0)
                draw_mandelbrot(vars, x, y);
            else if (ft_strcmp(vars->fractal_type, "julia") == 0)
                draw_julia(vars, x, y);
            else if (ft_strcmp(vars->fractal_type, "burningship") == 0)
                draw_burning_ship(vars, x, y);
        }
    }
}

void draw_fractal(t_vars *vars, char *fractal)
{
    if (ft_strcmp(fractal, "mandelbrot") == 0 || 
        ft_strcmp(fractal, "julia") == 0 || 
        ft_strcmp(fractal, "burningship") == 0)
    {
        vars->fractal_type = fractal;
        calculate_fractal(vars);
        mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img->img, 0, 0);
    }
    else
    {
        mlx_destroy_window(vars->mlx, vars->mlx_win);
        printf("Usage: ./fractol [mandelbrot/julia/burningship]\n");
        exit(EXIT_FAILURE);
    }
}




int main(int argc, char *argv[])
{
    t_vars vars;
    
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
