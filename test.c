#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	void *mlx;

	mlx = mlx_intit();
	mlx_loop(mlx);
}