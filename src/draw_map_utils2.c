#include "cub3D.h"

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
	t_vector			*origin;	
	mlx_image_t			*player;

	player = (*game_data)->player_data.player_image;
	origin = &(*game_data)->player_data.current_position;
	origin->x = player->instances[0].x;
	origin->y = player->instances[0].y;
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

void	add_bg_image(t_game **game_data)
{
	mlx_t		*mlx;

	mlx = (*game_data)->mlx;
	create_img(&(*game_data)->bg_img, mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	place_image((*game_data)->bg_img, mlx, 0, 0);
}
