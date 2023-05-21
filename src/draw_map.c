
#include "cub3D.h"

void	ft_hook(void *param)
{
	t_game				*game_data;
	mlx_t				*mlx;
	char				**map;

	game_data = param;
	map = game_data->map_data->map_array;
	mlx = game_data->mlx;
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

void	draw_line(struct s_position *pointA, struct s_static_position *pointB, mlx_image_t* y_img)
{
	double dX;
	double dY;
	double p;
	double x;
	double y;

	//bresenham algorithm
	x = pointA->x_axis;
	y = pointA->y_axis;
	dX = pointB->x_axis - x;
	dY = pointB->y_axis - y;
	p = 2 * dY- dX;
	printf("x is %f\n", x);
	printf("y is %f\n", y);
	printf("pointB->x is %f\n", pointB->x_axis);
	printf("pointB->y is %f\n", pointB->y_axis);
	while (x < pointB->x_axis)
	{
		if (p >= 0)
		{
			mlx_put_pixel(y_img, x++, y++, 0xFAFABB);
			p = p + (2 * dY) - (2 * dX);
		}
		else if (p < 0)
		{
			mlx_put_pixel(y_img, x++, y, 0xFAFABB);
			p = p + (2 * dY);
		}
	}
}

void	draw_ray(t_game *game_data)
{
	struct s_position			*origin;
	struct s_static_position	point;
	double x;
	double y;

	origin = &game_data->player_data.current_position;
	point.x_axis = origin->x_axis + 10;
	point.y_axis = origin->y_axis + 10;
	x = point.x_axis;
	y = point.y_axis;
	draw_line(origin, &point, game_data->bg_img);
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
	//draw player box;
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
	t_map		*map_data;

	mlx = (*game_data)->mlx;
	map_data = (*game_data)->map_data;
	create_img(&image, mlx, map_data->width, map_data->height);
	(*game_data)->bg_img = image;
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
	mlx_loop_hook(game_data->mlx, ft_hook, game_data);
	mlx_loop(game_data->mlx);
	mlx_terminate(game_data->mlx);
	destroy_map_data(map_data);
	free(game_data);
}
