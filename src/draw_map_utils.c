#include "cub3D.h"

int	get_color_texture(t_game **game_data, int topy)
{
	int				color;
	int				difference;
	int				x;
	int				y;
	char			**map;

	map = (*game_data)->map_data->map;
	difference = SCREEN_HEIGHT / 2 - (WALL_HEIGHT
			/ (*game_data)->distance) / 2;
	x = (int)(*game_data)->player_data.end_ray.x_axis;
	y = (int)(*game_data)->player_data.end_ray.y_axis;
	color = (return_south_texture(game_data, topy));
	if (difference < 0)
		topy += -difference;
	if ((y % TILE == 0 && map[(y) / TILE][(x - 1) / TILE] != '1'))
		color = (return_north_texture(game_data, topy));
	else if ((y % TILE == 1 && map[(y + 1) / TILE][(x) / TILE] == '1')
			&& x % TILE != 1)
		color = (return_south_texture(game_data, topy));
	else if (x % TILE == 0 && map[(y) / TILE][(x - 2) / TILE] == '1')
		color = (return_west_texture(game_data, topy));
	else if ((x % TILE == 1 && map[(y - 2) / TILE][(x) / TILE] == '1'))
		color = (return_east_texture(game_data, topy));
	return (color);
}

void	line_draw2(t_vector *pointA, struct s_position *pointB,
		char **map, t_game **game_data)
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	step;

	dx = (pointB->x_axis - pointA->x);
	dy = (pointB->y_axis - pointA->y);
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	x = pointA->x;
	y = pointA->y;
	while (map[(int)(y / TILE)][(int)(x / TILE)] != '1')
	{
		x += dx;
		y += dy;
	}
	(*game_data)->distance = sqrt(pow(pointA->x - x, 2)
			+ pow(pointA->y - y, 2));
	(*game_data)->player_data.end_ray.x_axis = x + 1;
	(*game_data)->player_data.end_ray.y_axis = y + 1;
}

void	draw_fov(t_game **game_data)
{
	t_vector			*origin;
	struct s_position	*point;
	double				fov_angle;
	double				fov_shit;
	t_int_vector		center;

	center = (t_int_vector){0, SCREEN_HEIGHT / 2};
	fov_angle = (*game_data)->player_data.angle - M_PI / 6;
	fov_shit = 0;
	origin = &(*game_data)->player_data.current_position;
	point = &(*game_data)->player_data.end_position;
	(void)point;
	update_origin(game_data);
	while (fov_angle < (*game_data)->player_data.angle + M_PI / 6)
	{
		update_end(game_data, fov_angle);
		line_draw2(origin, point, (*game_data)->map_data->map, game_data);
		draw_wall(game_data, center, fov_shit);
		fov_angle += DELTA_FOV;
		fov_shit += DELTA_FOV;
		center.x++;
	}
}
