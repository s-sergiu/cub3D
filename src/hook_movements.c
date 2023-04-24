
#include "cub3D.h"

void	turn_right(char **map, t_game *game_data)
{
	int					posx;
	int					posy;
	mlx_image_t			*player;

	player = game_data->player_data.player_image;
	posx = (*game_data->player_data.current_position.x_axis + 10)/ TILE;
	posy = (*game_data->player_data.current_position.y_axis + 9)/ TILE;
	if (map[posy][posx] != '1')
	{
		if (map[posy][(player->instances[0].x + 10) / TILE] != '1') 
			player->instances[0].x += 1;
	}
}

void	turn_left(char **map, t_game *game_data)
{
	int					posx;
	int					posy;
	mlx_image_t			*player;

	player = game_data->player_data.player_image;
	posx = (*game_data->player_data.current_position.x_axis)/ TILE;
	posy = (*game_data->player_data.current_position.y_axis - 10)/ TILE;
	if (map[posy][posx] != '1')
	{
		if (map[posy][(player->instances[0].x - 1) / TILE] != '1')
			player->instances[0].x -= 1;
	}
}

void	turn_down(char **map, t_game *game_data)
{
	int					posx;
	int					posy;
	mlx_image_t			*player;

	player = game_data->player_data.player_image;
	posx = (*game_data->player_data.current_position.x_axis + 9)/ TILE;
	posy = (*game_data->player_data.current_position.y_axis + 10)/ TILE;
	if (map[posy][posx] != '1')
	{
		if (map[(player->instances[0].y) / TILE][posx] != '1')
			player->instances[0].y += 1;
	}
}

void	turn_up(char **map, t_game *game_data)
{
	int					posx;
	int					posy;
	mlx_image_t			*player;

	player = game_data->player_data.player_image;
	posx = *game_data->player_data.current_position.x_axis / TILE;
	posy = *game_data->player_data.current_position.y_axis / TILE;
	if (map[posy][posx] != '1')
	{
		if (map[(player->instances[0].y - 1) / TILE][posx] != '1')
			player->instances[0].y -= 1;
	}
}
