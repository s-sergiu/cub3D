
#include "../include/cub3D.h"

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	draw_map(struct s_map_data *data)
{
	mlx_image_t* image;
	mlx_t* mlx;


	// Gotta error check this stuff
	if (!(mlx = mlx_init(data->width, data->height, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
	}
	if (!(image = mlx_new_image(mlx, data->width, data->height)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
	}
	memset(image->pixels, 255, data->width * data->height * 4);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
