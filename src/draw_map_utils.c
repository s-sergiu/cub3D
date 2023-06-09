#include "cub3D.h"

int	get_color_texture(t_game **game_data, int topy)
{
	int				color;
	int				difference;
	double			height;
	double			new_angle;
	double			fov_start;
	double			fov_end;

	height = WALL_HEIGHT / (*game_data)->distance;
	difference = SCREEN_HEIGHT / 2 - height / 2;
	new_angle = (*game_data)->player_data.angle;
	fov_end = fmod(new_angle - (M_PI / 6), 2 * M_PI);
	fov_start = fmod(new_angle + (M_PI / 6), 2 * M_PI);
	color = 0;
	if (difference < 0)
		topy += -difference;
	if (fov_end < 0)
		fov_end += 2 * M_PI;
	if ((int)((*game_data)->player_data.end_ray.y_axis) % TILE == 0)
		if (((fov_end >= M_PI) || fov_start >= M_PI)
			|| ((fov_end <= M_PI * 2 || fov_start >= 0)
				|| (fov_start < M_PI / 6)))
			return (return_north_texture(game_data, topy));
	if ((int)((*game_data)->player_data.end_ray.x_axis) % TILE == 0)
		if ((fov_end < 3 * M_PI_2) || (fov_start > M_PI_2))
			return (return_west_texture(game_data, topy));
	if ((int)((*game_data)->player_data.end_ray.y_axis) % TILE == 1)
		if ((fov_end <= 3 * M_PI_2) || (fov_start >= 3 * M_PI_2)
			|| (fov_end >= 0) || ((fov_start >= 0)
				&& (fov_start > 11 * M_PI / 6)))
			return (return_south_texture(game_data, topy));
	if ((int)((*game_data)->player_data.end_ray.x_axis) % TILE == 1)
		if ((fov_start > 3 * M_PI_2 || fov_start < 2 * M_PI)
			|| (fov_end < M_PI_2))
			return (return_east_texture(game_data, topy));
	return (color);
}

void	line_draw(t_vector *player, double angle, t_game **game_data)
{
	t_vector		d;
	t_vector		ray_direction;
	t_int_vector	map;
	t_vector		side_distance;
	t_vector		intersection;
	int				hit;
	double			distance;

	ray_direction.x = cos(angle);
	ray_direction.y = -sin(angle);
	player[0] = (t_vector)
	{(*game_data)->player_data.player_image->instances[0].x,
		(*game_data)->player_data.player_image->instances[0].y};
	map = (t_int_vector){player[0].x / TILE, player[0].y / TILE};
	if (ray_direction.x > 0)
		side_distance.x = ((map.x + 1) * TILE - player[0].x) / ray_direction.x;
	else if (ray_direction.x < 0)
		side_distance.x = ((map.x * TILE - player[0].x) / ray_direction.x);
	if (ray_direction.y > 0)
		side_distance.y = ((map.y + 1) * TILE - player[0].y) / ray_direction.y;
	else if (ray_direction.y < 0)
		side_distance.y = (map.y * TILE - player[0].y) / ray_direction.y;
	d.x = fabs(TILE / ray_direction.x);
	d.y = fabs(TILE / ray_direction.y);
	hit = 0;
	while ((*game_data)->map_data->map_array[map.y][map.x] == '0')
	{
		if (side_distance.x < side_distance.y)
		{
			side_distance.x += d.x;
			map.x += (ray_direction.x > 0) - (ray_direction.x < 0);
			if (ray_direction.x > 0)
				(*game_data)->hit = EAST;
			else
				(*game_data)->hit = WEST;
		}
		else
		{
			side_distance.y += d.y;
			map.y = (ray_direction.y > 0) - (ray_direction.y < 0);
			if (ray_direction.y > 0)
				(*game_data)->hit = NORTH;
			else
				(*game_data)->hit = SOUTH;
		}
	}
	if (hit == EAST || hit == WEST)
	{
		intersection.x = map.x * TILE + (ray_direction.x > 0 ? 0 : TILE);
		intersection.y = player[0].y + (intersection.x
				- player[0].x) * tan(angle);
	}
	else
	{
		intersection.y = map.y * TILE + (ray_direction.y > 0 ? 0 : TILE);
		intersection.x = player[0].x + (intersection.y
				- player[0].y) / tan(angle);
	}
	distance = sqrt(pow(intersection.x - player[0].x, 2)
			+ pow(intersection.y - player[0].y, 2));
	(*game_data)->distance = distance;
	(*game_data)->player_data.end_ray.x_axis = intersection.x;
	(*game_data)->player_data.end_ray.y_axis = intersection.y;
}

void	line_draw2(t_vector *pointA, struct s_position *pointB,
		char **map, t_game *game_data)
{
	double	x;
	double	y;
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	double	dx;
	double	dy;
	double	step;
	int		i;
	double	distance;

	x1 = pointA->x;
	y1 = pointA->y;
	x2 = pointB->x_axis;
	y2 = pointB->y_axis;
	dx = (x2 - x1);
	dy = (y2 - y1);
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	x = x1;
	y = y1;
	i = -1;
	while (++i <= step)
	{
		if (map[(int)(y / TILE)][(int)(x / TILE)] == '1')
		{
			distance = sqrt(pow(x1 - x, 2) + pow(y1 - y, 2));
			game_data->distance = distance;
			game_data->player_data.end_ray.x_axis = x + 1;
			game_data->player_data.end_ray.y_axis = y + 1;
			return ;
		}
		else
		{
			x += dx;
			y += dy;
		}
	}
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
		//line_draw(origin, fov_angle, game_data);
		line_draw2(origin, point, (*game_data)->map_data->map, (*game_data));
		draw_wall(game_data, center, fov_shit);
		fov_angle += DELTA_FOV;
		fov_shit += DELTA_FOV;
		center.x++;
	}
}
