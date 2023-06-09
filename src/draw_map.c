#include "cub3D.h"

void	draw_scene(t_game **game_data)
{
	draw_ray(game_data);
	draw_ceiling(game_data);
	draw_floor(game_data);
}

void	ft_hook(void *param)
{
	t_game			*game_data;
	static double	sum;

	game_data = param;
	if (sum > 0.0007)
	{
		if (mlx_is_key_down(game_data->mlx, MLX_KEY_ESCAPE))
			mlx_close_window(game_data->mlx);
		if (mlx_is_key_down(game_data->mlx, MLX_KEY_W))
			press_w(game_data->map_data->map, game_data);
		if (mlx_is_key_down(game_data->mlx, MLX_KEY_S))
			press_s(game_data->map_data->map, game_data);
		if (mlx_is_key_down(game_data->mlx, MLX_KEY_A))
			press_a(game_data->map_data->map, game_data);
		if (mlx_is_key_down(game_data->mlx, MLX_KEY_D))
			press_d(game_data->map_data->map, game_data);
		if (mlx_is_key_down(game_data->mlx, MLX_KEY_LEFT))
			press_left(&game_data);
		if (mlx_is_key_down(game_data->mlx, MLX_KEY_RIGHT))
			press_right(&game_data);
		draw_scene(&game_data);
		sum = 0;
	}
	sum += game_data->mlx->delta_time;
}

void	draw_map_player(t_game **game_data)
{
	mlx_image_t	*player;
	mlx_t		*mlx;
	int			x;
	int			y;
	int			color;

	mlx = (*game_data)->mlx;
	player = NULL;
	create_img(&player, mlx, 5, 5);
	x = (*game_data)->player_data.initial_position.x_axis;
	y = (*game_data)->player_data.initial_position.y_axis;
	(*game_data)->player_data.map_player = player;
	place_image(player, mlx, (x * 5), (y * 5));
	color = get_rgba(255, 0, 0, 255);
	while (y < 5)
	{
		while (x < 5)
		{
			mlx_put_pixel(player, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_player(t_game **game_data)
{
	mlx_image_t	*player;
	mlx_t		*mlx;
	int			x;
	int			y;

	mlx = (*game_data)->mlx;
	player = NULL;
	create_img(&player, mlx, 5, 5);
	(*game_data)->player_data.player_image = player;
	x = (*game_data)->player_data.initial_position.x_axis;
	y = (*game_data)->player_data.initial_position.y_axis;
	place_image(player, mlx, (x * TILE) + 16, (y * TILE) + 16);
	(*game_data)->player_data.current_position.x = player->instances[0].x;
	(*game_data)->player_data.current_position.y = player->instances[0].y;
}

void	game_setup(t_memory **block, char *argv)
{
	t_game	*game_data;
	t_map	*map_data;

	game_data = NULL;
	map_data = NULL;
	init_game_data(block, &game_data);
	init_map_data(block, &game_data, &map_data, argv);
	game_data->map_data = map_data;
	add_ceiling(&game_data);
	add_floor(&game_data);
	draw_walls(game_data);
	draw_player(&game_data);
	add_bg_image(&game_data);
	mlx_loop_hook(game_data->mlx, ft_hook, game_data);
	mlx_loop(game_data->mlx);
	mlx_terminate(game_data->mlx);
	mlx_delete_texture(game_data->north);
	mlx_delete_texture(game_data->south);
	mlx_delete_texture(game_data->east);
	mlx_delete_texture(game_data->west);
}
