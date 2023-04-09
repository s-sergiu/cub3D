
#include "../include/cub3D.h"

void	draw_map(char **map)
{
	mlx_image_t* image;
	struct	s_map_data *data;
	mlx_t* mlx;


	data = get_width_and_height(map);	
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
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
