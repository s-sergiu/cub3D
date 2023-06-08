#include "cub3D.h"

void	draw_ceiling(t_game **game_data)
{
	unsigned int	x0;
	unsigned int	y0;

	x0 = 0;
	y0 = -1;
	while (++y0 < SCREEN_HEIGHT / 2)
	{
		while (x0 < SCREEN_WIDTH)
			mlx_put_pixel((*game_data)->ceiling, x0++,
				y0, (*game_data)->ceiling_color);
		x0 = 0;
	}
}

void	draw_floor(t_game **game_data)
{
	unsigned int	x0;
	unsigned int	y0;

	x0 = 0;
	y0 = -1;
	while (++y0 < SCREEN_HEIGHT / 2)
	{
		while (x0 < SCREEN_WIDTH)
			mlx_put_pixel((*game_data)->floor, x0++,
				y0, (*game_data)->floor_color);
		x0 = 0;
	}
}

void	ft_hook(void *param)
{
	t_game			*game_data;
	mlx_t			*mlx;
	char			**map;
	static double	sum;

	game_data = param;
	map = game_data->map_data->map;
	mlx = game_data->mlx;
	if (sum > 0.0007)
	{
		if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
			mlx_close_window(mlx);
		if (mlx_is_key_down(mlx, MLX_KEY_W))
			press_w(map, game_data);
		if (mlx_is_key_down(mlx, MLX_KEY_S))
			press_s(map, game_data);
		if (mlx_is_key_down(mlx, MLX_KEY_A))
			press_a(map, game_data);
		if (mlx_is_key_down(mlx, MLX_KEY_D))
			press_d(map, game_data);
		if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
			press_left(&game_data);
		if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
			press_right(&game_data);
		draw_ray(&game_data);
		draw_ceiling(&game_data);
		draw_floor(&game_data);
		sum = 0;
	}
	sum += mlx->delta_time;
}

void	draw_walls(t_game *game_data)
{
	char			**map;
	int				x;
	int				y;

	x = 0;
	y = 0;
	map = game_data->map_data->map;
	while (map[y])
	{
		while (map[y][x])
			place_wall_or_player(map, game_data, x++, y);
		y++;
		x = 0;
	}
}

void	update_origin(t_game **game_data)
{
	struct s_position	*origin;	
	mlx_image_t			*player;

	player = (*game_data)->player_data.player_image;
	origin = &(*game_data)->player_data.current_position;
	origin->x_axis = player->instances[0].x;
	origin->y_axis = player->instances[0].y;
}

void	update_end(t_game **game_data, double fov_angle)
{
	struct s_position	*end;	
	mlx_image_t			*player;

	player = (*game_data)->player_data.player_image;
	end = &(*game_data)->player_data.end_position;
	end->x_axis = player->instances[0].x + INT_MAX * cos(fov_angle);
	end->y_axis = player->instances[0].y + INT_MAX * sin(fov_angle);
}

void	draw_ray(t_game **game_data)
{
	mlx_image_t			*img;

	img = (*game_data)->bg_img;
	ft_bzero(img->pixels, img->width * img->height * 4);
	draw_fov(game_data);
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
	int			color;

	mlx = (*game_data)->mlx;
	player = NULL;
	create_img(&player, mlx, 5, 5);
	(*game_data)->player_data.player_image = player;
	x = (*game_data)->player_data.initial_position.x_axis;
	y = (*game_data)->player_data.initial_position.y_axis;
	place_image(player, mlx, (x * TILE) + 16, (y * TILE) + 16);
	(*game_data)->player_data.current_position.x_axis = player->instances[0].x;
	(*game_data)->player_data.current_position.y_axis = player->instances[0].y;
	color = get_rgba(0, 0, 0, 255);
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

void	add_bg_image(t_game **game_data)
{
	mlx_t		*mlx;

	mlx = (*game_data)->mlx;
	create_img(&(*game_data)->bg_img, mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	place_image((*game_data)->bg_img, mlx, 0, 0);
}

void	add_floor(t_game **game_data)
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	unsigned int	x0;
	unsigned int	y0;

	mlx = (*game_data)->mlx;
	create_img(&image, mlx, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
	(*game_data)->floor = image;
	x0 = 0;
	y0 = SCREEN_HEIGHT / 2;
	place_image(image, mlx, x0, y0);
	set_img_color(image, 255);
}

void	add_ceiling(t_game **game_data)
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	unsigned int	x0;
	unsigned int	y0;

	mlx = (*game_data)->mlx;
	create_img(&image, mlx, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
	(*game_data)->ceiling = image;
	x0 = 0;
	y0 = 0;
	place_image(image, mlx, x0, y0);
	set_img_color(image, 255);
}

void	add_game_screen(t_game **game_data)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = (*game_data)->mlx;
	create_img(&image, mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	(*game_data)->game_screen = image;
	place_image(image, mlx, 0, 0);
	set_img_color(image, 255);
}

void	game_setup(char *argv)
{
	t_game	*game_data;
	t_map	*map_data;

	game_data = NULL;
	map_data = NULL;
	init_game_data(&game_data, map_data);
	init_map_data(&game_data, &map_data, argv);
	game_data->map_data = map_data;
	add_ceiling(&game_data);
	add_floor(&game_data);
	draw_walls(game_data);
	draw_player(&game_data);
	add_bg_image(&game_data);
	mlx_loop_hook(game_data->mlx, ft_hook, game_data);
	mlx_loop(game_data->mlx);
	mlx_terminate(game_data->mlx);
	destroy_map_data(map_data);
	free(game_data);
}
