
#include "../include/cub3D.h"

void	draw_map(void)
{
	mlx_image_t* image;
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(9, 8, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
	}
	if (!(image = mlx_new_image(mlx, 9, 8)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
	}
	memset(image->pixels, 255, 9 * 8 * 4);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
