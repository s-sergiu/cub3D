#include "cub3D.h"

void	press_d(char **map, t_game *game_data)
{
	int					posx;
	int					posy;
	t_vector			d;
	mlx_image_t			*player_img;
	t_player			player;

	d = (t_vector){0, 0};
	(void)d;
	player_img = game_data->player_data.player_image;
	player = game_data->player_data;
	d.x = sin(player.angle) * -1.0 * SPEED;
	d.y = cos(player.angle) * SPEED;
	posx = (player_img->instances[0].x + (int)d.x) / TILE;
	posy = (player_img->instances[0].y + (int)d.y) / TILE;
	if (map[posy][posx] != '1')
	{
		player_img->instances[0].x += d.x;
		player_img->instances[0].y += d.y;
	}
}

void	press_a(char **map, t_game *game_data)
{
	int					posx;
	int					posy;
	t_vector			d;
	mlx_image_t			*player_img;
	t_player			player;

	d = (t_vector){0, 0};
	(void)d;
	player_img = game_data->player_data.player_image;
	player = game_data->player_data;
	d.x = sin(player.angle) * SPEED;
	d.y = cos(player.angle) * -1.0 * SPEED;
	posx = (player_img->instances[0].x + (int)d.x) / TILE;
	posy = (player_img->instances[0].y + (int)d.y) / TILE;
	if (map[posy][posx] != '1')
	{
		player_img->instances[0].x += d.x;
		player_img->instances[0].y += d.y;
	}
}

void	press_w(char **map, t_game *game_data)
{
	int					posx;
	int					posy;
	t_vector			d;
	mlx_image_t			*player_img;
	t_player			player;

	d = (t_vector){0, 0};
	(void)d;
	player_img = game_data->player_data.player_image;
	player = game_data->player_data;
	d.x = cos(player.angle) * SPEED;
	d.y = sin(player.angle) * SPEED;
	posx = (player_img->instances[0].x + (int)d.x) / TILE;
	posy = (player_img->instances[0].y + (int)d.y) / TILE;
	if (map[posy][posx] != '1')
	{
		player_img->instances[0].x += d.x;
		player_img->instances[0].y += d.y;
	}
}

void	press_s(char **map, t_game *game_data)
{
	int					posx;
	int					posy;
	t_vector			d;
	mlx_image_t			*player_img;
	t_player			player;

	d = (t_vector){0, 0};
	(void)d;
	player_img = game_data->player_data.player_image;
	player = game_data->player_data;
	d.x = cos(player.angle) * -1.0 * SPEED;
	d.y = sin(player.angle) * -1.0 * SPEED;
	posx = (player_img->instances[0].x + (int)d.x) / TILE;
	posy = (player_img->instances[0].y + (int)d.y) / TILE;
	if (map[posy][posx] != '1')
	{
		player_img->instances[0].x += d.x;
		player_img->instances[0].y += d.y;
	}
}

void	press_left(t_game **data)
{
	t_player	*player;

	player = &(*data)->player_data;
	player->angle -= ANGLE_SPEED;
}

void	press_right(t_game **data)
{
	t_player	*player;

	player = &(*data)->player_data;
	player->angle += ANGLE_SPEED;
}
