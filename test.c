#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
}			t_vars;

int render_next_frame(t_vars *vars)
{

}

int	main(void)
{
	t_vars vars;

	vars.mlx = mlx_intit();
	vars.mlx_win = mlx_new_window(vars.mlx, 960, 540, "Hello world!");
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
}
