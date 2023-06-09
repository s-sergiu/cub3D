#include "cub3D.h"

int	get_color_texture(mlx_texture_t *tex, t_game *game_data, int topy)
{
	int				position;
	int				color;
	int				texture_x;
	int				texture_y;
	double			x;
	double			y;
	int				difference;
	double			height;
	double			new_angle;
	double			fov_start;
	double			fov_end;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;

	north = game_data->north;
	south = game_data->south;
	east = game_data->east;
	west = game_data->west;
	(void)north;
	(void)south;
	(void)east;
	(void)west;
	(void)game_data;
	(void)y;
	height = (WALL_HEIGHT / game_data->distance);
	(void)tex;
	y = game_data->player_data.end_ray.y_axis;
	x = game_data->player_data.end_ray.x_axis;
	(void)x;
	difference = SCREEN_HEIGHT / 2 - height / 2;
	new_angle = game_data->player_data.angle;
	fov_end = fmod(new_angle - (M_PI / 6), 2 * M_PI);
	fov_start = fmod(new_angle + (M_PI / 6), 2 * M_PI);
	(void)fov_start;
	color = 0;
	if (difference < 0)
		topy += -difference;
	if (fov_end < 0)
		fov_end += 2 * M_PI;
	if ((int)y % TILE == 0)
	{
		if (((fov_end >= M_PI) || fov_start >= M_PI)
			|| ((fov_end <= M_PI * 2 || fov_start >= 0)
				|| (fov_start < M_PI / 6)))
		{
			texture_y = (topy) * ((double)north->height - 1) / height;
			texture_x = fmod((x / TILE), 1.0) * north->width;
			position = (texture_y * north->width + texture_x)
				* north->bytes_per_pixel;
			color = get_rgba(north->pixels[position],
					north->pixels[position + 1], north->pixels[position + 2],
					north->pixels[position + 3]);
			return (color);
		}
	}
	if ((int)x % TILE == 0)
	{
		if ((fov_end < 3 * M_PI_2) || (fov_start > M_PI_2))
		{
			texture_y = (topy) * ((double)west->height - 1) / height;
			texture_x = fmod((y / TILE), 1.0) * west->width;
			position = (texture_y * west->width + texture_x)
				* west->bytes_per_pixel;
			color = get_rgba(west->pixels[position],
					west->pixels[position + 1], west->pixels[position + 2],
					west->pixels[position + 3]);
			return (color);
		}
	}
	if ((int)y % TILE == 1)
	{
		if ((fov_end <= 3 * M_PI_2) || (fov_start >= 3 * M_PI_2)
			|| (fov_end >= 0) || ((fov_start >= 0)
				&& (fov_start > 11 * M_PI / 6)))
		{
			texture_y = (topy) * ((double)south->height - 1) / height;
			texture_x = fmod((x / TILE), 1.0) * south->width;
			position = ((texture_y) * south->width
					+ (south->width - 1 - texture_x)) * south->bytes_per_pixel;
			color = get_rgba(south->pixels[position],
					south->pixels[position + 1], south->pixels[position + 2],
					south->pixels[position + 3]);
			return (color);
		}
	}
	if ((int)x % TILE == 1)
	{
		if ((fov_start > 3 * M_PI_2 || fov_start < 2 * M_PI)
			|| (fov_end < M_PI_2))
		{
			texture_y = (topy) * ((double)east->height - 1) / height;
			texture_x = fmod((y / TILE), 1.0) * east->width;
			position = (texture_y * east->width + texture_x)
				* east->bytes_per_pixel;
			color = get_rgba(east->pixels[position],
					east->pixels[position + 1], east->pixels[position + 2],
					east->pixels[position + 3]);
			return (color);
		}
	}
	return (color);
}

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
			color = get_color_texture((*game_data)->north,
					(*game_data), topy - posy);
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
