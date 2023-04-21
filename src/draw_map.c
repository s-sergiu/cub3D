
#include "cub3D.h"

void	ft_hook(void *param)
{
	t_game				*game_data;
	mlx_t				*mlx;
	char				**map;

	game_data = param;
	map = game_data->map_data->map_array;
	mlx = game_data->mlx_handle;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		turn_up(map, game_data);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		turn_down(map, game_data);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		turn_left(map, game_data);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		turn_right(map, game_data);
}

void	draw_walls(t_game *game_data)
{
	char			**map;
	int				x;
	int				y;

	x = 0;
	y = 0;
	map = game_data->map_data->map_array;
	while (map[y])
	{
		while (map[y][x])
			place_wall_or_player(map, game_data, x++, y);
		y++;
		x = 0;
	}
}

void	draw_player(t_game **game_data)
{
	mlx_image_t	*player;
	mlx_t		*mlx;
	int			x;
	int			y;

	mlx = (*game_data)->mlx_handle;
	(*game_data)->player_data.player_image = mlx_new_image(mlx, 10, 10);
	player = (*game_data)->player_data.player_image;
	x = (*game_data)->player_data.initial_position.x_axis;
	y = (*game_data)->player_data.initial_position.y_axis;
	mlx_image_to_window(mlx, player, (x * TILE) + 28, (y * TILE) + 28);
	(*game_data)->player_data.current_position.x_axis = &player->instances[0].x;
	(*game_data)->player_data.current_position.y_axis = &player->instances[0].y;
	x = -1;
	y = 0;
	while (++x < (int)player->width)
	{
		while (y < (int)player->height)
			mlx_put_pixel(player, x, y++, 240);
		y = 0;
	}
}

void	add_bg_image(t_game **game_data)
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int			width;
	int			height;

	width = (*game_data)->map_data->width;
	height = (*game_data)->map_data->height;
	mlx = (*game_data)->mlx_handle;
	image = (*game_data)->mlx_background_image;
	place_image(image, mlx, 0, 0);
	memset(image->pixels, 255, width * height * sizeof(int));
}

void	game_setup(char *argv)
{
	t_game	*game_data;
	t_map	*map_data;

	game_data = NULL;
	map_data = NULL;
	init_map_data(&map_data, argv);
	init_game_data(&game_data, map_data);
	add_bg_image(&game_data);
	draw_grid(map_data, game_data->mlx_background_image);
	draw_walls(game_data);
	draw_player(&game_data);
	mlx_loop_hook(game_data->mlx_handle, ft_hook, game_data);
	mlx_loop(game_data->mlx_handle);
	mlx_terminate(game_data->mlx_handle);
}
