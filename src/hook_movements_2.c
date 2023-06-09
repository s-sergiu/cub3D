#include "cub3D.h"

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
