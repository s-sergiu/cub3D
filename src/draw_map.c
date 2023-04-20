
#include "cub3D.h"

void	ft_hook(void *param)
{
	t_game				*game_data;
	mlx_t				*mlx;
	mlx_image_t			*player;
	char				**map;
	int					posx;
	int					posy;

	game_data = param;
	map = game_data->map_data->map_array;
	mlx = game_data->mlx_handle;
	player = game_data->player_data.player_image;
	posx = *game_data->player_data.current_position.xAxis / TILE;
	posy = *game_data->player_data.current_position.yAxis / TILE;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		if (map[posy][posx] != '1')
		{
			if (map[(player->instances[0].y - 1) / TILE][posx] != '1')
				player->instances[0].y -= 1;
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		if (map[posy][posx] != '1')
		{
			if (map[(player->instances[0].y + 5) / TILE][posx] != '1')
				player->instances[0].y += 1;
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		if (map[posy][posx] != '1')
		{
			if (map[posy][(player->instances[0].x - 1) / TILE] != '1')
				player->instances[0].x -= 1;
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		if (map[posy][posx] != '1')
		{
			if (map[posy][(player->instances[0].x + 5) / TILE] != '1')
				player->instances[0].x += 1;
		}
	}
}

void	draw_walls(t_game *game_data)
{
	mlx_image_t		*img;
	mlx_t			*mlx;
	t_map			*map_data;
	int				x;
	int				y;

	x = 0;
	y = 0;
	map_data = game_data->map_data;
	mlx = game_data->mlx_handle;
	while (map_data->map_array[y])
	{
		while (map_data->map_array[y][x])
		{
			if (map_data->map_array[y][x] == '1')
			{
				img = mlx_new_image(mlx, TILE, TILE);
				mlx_image_to_window(mlx, img, x * TILE, y * TILE);
				memset(img->pixels, 120, TILE * TILE * 4);
			}
			if (map_data->map_array[y][x] == 'P')
			{
				game_data->player_data.initial_position.xAxis = x;
				game_data->player_data.initial_position.yAxis = y;
			}
			x++;
		}
		y++;
		x = 0;
	}
}

void	draw_player(t_game *game_data)
{
	mlx_image_t			*player;
	int					x;
	int					y;

	game_data->player_data.player_image = mlx_new_image(game_data->mlx_handle, 5, 5);
	player = game_data->player_data.player_image;
	x = game_data->player_data.initial_position.xAxis;
	y = game_data->player_data.initial_position.yAxis;
	mlx_image_to_window(game_data->mlx_handle, player, (x * TILE) + 28, (y * TILE) + 28);
	game_data->player_data.current_position.xAxis = &player->instances[0].x;
	game_data->player_data.current_position.yAxis = &player->instances[0].y;
	for (uint32_t z = 0; z < player->width; ++z)
	{
		for (uint32_t b = 0; b < player->height; ++b)
		{
			mlx_put_pixel(player, z, b, 240);
		}
	}
}

void	draw_grid(t_map *map_data, mlx_image_t *image)
{
	int	x;
	int	y;

	x = 0;
	y = TILE;
	while (y < map_data->height)
	{
		while (x < map_data->width)
			mlx_put_pixel(image, x++, y, 231);
		y += TILE;
		x = 0;
	}
	y = 0;
	while (x < map_data->width)
	{
		while (y < map_data->height)
			mlx_put_pixel(image, x, y++, 255);
		x += TILE;
		y = 0;
	}
}

void	place_image_to_screen(t_game **game_data,
							t_map *map_data)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = (*game_data)->mlx_handle;
	image = (*game_data)->mlx_background_image;
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
	memset(image->pixels, 255, map_data->width * map_data->height * 4);
}

void	draw_map(t_map *map_data)
{
	t_game	*game_data;

	game_data = NULL;
	init_game_data(&game_data, map_data);
	place_image_to_screen(&game_data, map_data);
	draw_grid(map_data, game_data->mlx_background_image);
	draw_walls(game_data);
	draw_player(game_data);
	mlx_loop_hook(game_data->mlx_handle, ft_hook, game_data);
	mlx_loop(game_data->mlx_handle);
	mlx_terminate(game_data->mlx_handle);
}
