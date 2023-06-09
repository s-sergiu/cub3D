#include "cub3D.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_wall(t_game **game_data, t_int_vector center, double fov)
{
	double			height;
	unsigned int	x0;
	int				topy;
	int				posy;
	int				color;

	(*game_data)->distance *= (cos(M_PI / 6 - fov));
	height = WALL_HEIGHT / (*game_data)->distance;
	topy = SCREEN_HEIGHT / 2 - height / 2;
	if (topy < 0)
		topy = 0;
	x0 = center.x;
	posy = topy;
	while (topy <= center.y + (height / 2) && topy <= SCREEN_HEIGHT - 1)
	{
		while (x0 < center.x + 1)
		{
			color = get_color_texture(game_data, topy - posy);
			mlx_put_pixel((*game_data)->bg_img, x0++, topy, color);
		}
		x0 = center.x;
		topy++;
	}
}

void	player_angle(t_game **data, char orientation)
{
	if (orientation == 'E')
		(*data)->player_data.angle = 0;
	else if (orientation == 'S')
		(*data)->player_data.angle = M_PI_2;
	else if (orientation == 'W')
		(*data)->player_data.angle = M_PI;
	else if (orientation == 'N')
		(*data)->player_data.angle = 3 * M_PI_2;
}
