
#include "cub3D.h"

void	place_wall_or_player(char **map, t_game *game_data, int x, int y)
{
	mlx_image_t	*img;
	mlx_t		*mlx;

	mlx = game_data->mlx_handle;
	if (map[y][x] == '1')
	{
		img = mlx_new_image(mlx, TILE, TILE);
		mlx_image_to_window(mlx, img, x * TILE, y * TILE);
		memset(img->pixels, 120, TILE * TILE * sizeof(int));
	}
	if (map[y][x] == 'P')
	{
		game_data->player_data.initial_position.x_axis = x;
		game_data->player_data.initial_position.y_axis = y;
	}
}

void	add_img(mlx_image_t *img, mlx_t *mlx, int width, int height)
{
	if (mlx_image_to_window(mlx, img, width, height) == -1)
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
}
