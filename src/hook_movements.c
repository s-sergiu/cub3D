
#include "cub3D.h"

void	turn_right(char **map, t_game *game_data)
{
	int					posx;
	int					posy;
	mlx_image_t			*player;

	player = game_data->player_data.player_image;
	posx = (player->instances[0].x + 1)/ TILE;
	posy = (player->instances[0].y )/ TILE;
	if (map[posy][posx] != '1') 
		player->instances[0].x += 1;
	draw_ray(game_data);
}

void	turn_left(char **map, t_game *game_data)
{
	int					posx;
	int					posy;
	mlx_image_t			*player;

	player = game_data->player_data.player_image;
	posx = (player->instances[0].x - 2)/ TILE;
	posy = (player->instances[0].y)/ TILE;
	if (map[posy][posx] != '1') 
		player->instances[0].x -= 1;
	draw_ray(game_data);
}

void	turn_down(char **map, t_game *game_data)
{
	int					posx;
	int					posy;
	mlx_image_t			*player;

	player = game_data->player_data.player_image;
	posx = (player->instances[0].x)/ TILE;
	posy = (player->instances[0].y + 1)/ TILE;
	if (map[posy][posx] != '1') 
		player->instances[0].y += 1;
	draw_ray(game_data);
}

void	turn_up(char **map, t_game *game_data)
{
	int					posx;
	int					posy;
	mlx_image_t			*player;

	player = game_data->player_data.player_image;
	posx = (player->instances[0].x)/ TILE;
	posy = (player->instances[0].y - 2)/ TILE;
	if (map[posy][posx] != '1') 
		player->instances[0].y -= 1;
	draw_ray(game_data);
}
