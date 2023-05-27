
#include "cub3D.h"

void	ft_hook(void *param)
{
	t_game	*game_data;
	mlx_t	*mlx;
	char	**map;
	static double sum;

	game_data = param;
	map = game_data->map_data->map_array;
	mlx = game_data->mlx;
	if (sum < 0.9)
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
	map = game_data->map_data->map_array;
	while (map[y])
	{
		while (map[y][x])
			place_wall_or_player(map, game_data, x++, y);
		y++;
		x = 0;
	}
}

void	draw_line(struct s_position *pointA, struct s_position *pointB, mlx_image_t* y_img)
{
	double dX;
	double dY;
	double m;
	double error;
	int x;
	int y;

	//bresenham algorithm
	error = 0.5;
	x = pointA->x_axis;
	y = pointA->y_axis;
	dX = pointB->x_axis - x;
	dY = pointB->y_axis - y;
	m = dY/dX;
	while (x < pointB->x_axis)
	{
		mlx_put_pixel(y_img, x, y, 0xFAFABB);
		x++;
		error += m;
		if (error > 0.5)
		{
			y++;
			error += -1;
		}
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

void	draw_player(t_game **game_data)
{
	mlx_image_t	*player;
	mlx_t		*mlx;
	int			x;
	int			y;

	mlx = (*game_data)->mlx;
	player = NULL;
	//create new player image;
	create_img(&player, mlx, 1, 1);
	//assign player image in my struct the pointer I created;
	(*game_data)->player_data.player_image = player;
	//get_player initial position;
	x = (*game_data)->player_data.initial_position.x_axis;
	y = (*game_data)->player_data.initial_position.y_axis;
	// place player to window;
	place_image(player, mlx, (x * TILE) + 32, (y * TILE) + 32);
	//get player current position;
	(*game_data)->player_data.current_position.x_axis = player->instances[0].x;
	(*game_data)->player_data.current_position.y_axis = player->instances[0].y;
	(*game_data)->player_data.end_position.x_axis = player->instances[0].x;
	(*game_data)->player_data.end_position.y_axis = player->instances[0].y + 100;
	//draw player box;
	x = -1;
	y = 0;
	while (++x < (int)player->width)
	{
		while (y < (int)player->height)
			mlx_put_pixel(player, x, y++, 0);
		y = 0;
	}
}

void	add_bg_image(t_game **game_data)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = (*game_data)->mlx;
	create_img(&image, mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	(*game_data)->bg_img = image;
	place_image(image, mlx, 0, 0);
	set_img_color(image, 255);
}

void	add_floor(t_game **game_data)
{
	mlx_t		*mlx;
	mlx_texture_t	*texture;

	mlx = (*game_data)->mlx;
	texture = mlx_load_png("data/textures/blue.png");
	(*game_data)->floor = mlx_texture_to_image(mlx, texture);
	place_image((*game_data)->floor, mlx, 0, 512);
}

void	add_ceiling(t_game **game_data)
{
	mlx_t		*mlx;
	mlx_texture_t	*texture;

	mlx = (*game_data)->mlx;
	texture = mlx_load_png("data/textures/yellow.png");
	(*game_data)->floor = mlx_texture_to_image(mlx, texture);
	place_image((*game_data)->ceiling, mlx, 0, 0);
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
	init_map_data(&map_data, argv);
	init_game_data(&game_data, map_data);
	add_bg_image(&game_data);
	draw_grid(map_data, game_data->bg_img);
	draw_walls(game_data);
	draw_player(&game_data);
	add_bg_image(&game_data);
	mlx_loop_hook(game_data->mlx, ft_hook, game_data);
	mlx_loop(game_data->mlx);
	mlx_terminate(game_data->mlx);
	destroy_map_data(map_data);
	free(game_data);
}
