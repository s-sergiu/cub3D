#include "cub3D.h"

void	set_img_color(mlx_image_t *img, uint32_t color_value)
{
	memset(img->pixels, color_value, img->width
		* img->height * sizeof(int32_t));
}

void	create_img(mlx_image_t **img, mlx_t *mlx, int width, int height)
{
	(*img) = mlx_new_image(mlx, width, height);
	if (!img)
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
}

void	place_image(mlx_image_t *img, mlx_t *mlx, int width, int height)
{
	if (mlx_image_to_window(mlx, img, width, height) == -1)
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
}

void	place_wall_or_player(char **map, t_game *game_data, int x, int y)
{
	if (map[y][x] == 'N' || map[y][x] == 'S'
			|| map[y][x] == 'W' || map[y][x] == 'E')
	{
		game_data->player_data.initial_position.x_axis = x;
		game_data->player_data.initial_position.y_axis = y;
	}
}
