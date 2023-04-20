
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
	mlx_image_t	*player;
	int			x;
	int			y;
	int			i;
	int			j;

	game_data->player_data.player_image = mlx_new_image(game_data->mlx_handle, 5, 5);
	player = game_data->player_data.player_image;
	x = game_data->player_data.initial_position.xAxis;
	y = game_data->player_data.initial_position.yAxis;
	mlx_image_to_window(game_data->mlx_handle, player, (x * TILE) + 28, (y * TILE) + 28);
	game_data->player_data.current_position.xAxis = &player->instances[0].x;
	game_data->player_data.current_position.yAxis = &player->instances[0].y;
	i = -1;
	j = 0;
	while (++i < (int)player->width)
	{
		while (j < (int)player->height)
		{
			mlx_put_pixel(player, i, j, 240);
			j++;
		}
		j = 0;
	}
}

void	draw_horizontal_line(int height, int width, mlx_image_t *image)
{
	int	x;
	int	y;

	x = 0;
	y = TILE;
	while (y < height)
	{
		while (x < width)
			mlx_put_pixel(image, x++, y, 231);
		y += TILE;
		x = 0;
	}
}

void	draw_vertical_line(int height, int width, mlx_image_t *image)
{
	int	x;
	int	y;

	y = 0;
	x = TILE;
	while (x < width)
	{
		while (y < height)
			mlx_put_pixel(image, x, y++, 255);
		x += TILE;
		y = 0;
	}
}

void	draw_grid(t_map *map_data, mlx_image_t *image)
{
	int	height;
	int	width;

	height = map_data->height;
	width = map_data->width;
	draw_horizontal_line(height, width, image);
	draw_vertical_line(height, width, image);
}

void	add_img(mlx_image_t *img, mlx_t *mlx, int width, int height)
{
	if (mlx_image_to_window(mlx, img, width, height) == -1)
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
}

void	add_bg_image(t_game **game_data, t_map *map_data)
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int			width;
	int			height;

	width = map_data->width;
	height = map_data->height;
	mlx = (*game_data)->mlx_handle;
	image = (*game_data)->mlx_background_image;
	add_img(image, mlx, 0, 0);
	memset(image->pixels, 255, width * height * 4);
}

void	draw_map(t_map *map_data)
{
	t_game	*game_data;

	game_data = NULL;
	init_game_data(&game_data, map_data);
	add_bg_image(&game_data, map_data);
	draw_grid(map_data, game_data->mlx_background_image);
	draw_walls(game_data);
	draw_player(game_data);
	mlx_loop_hook(game_data->mlx_handle, ft_hook, game_data);
	mlx_loop(game_data->mlx_handle);
	mlx_terminate(game_data->mlx_handle);
}
