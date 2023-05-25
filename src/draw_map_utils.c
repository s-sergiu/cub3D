
#include "cub3D.h"

void	player_angle(t_game *data, char orientation)
{
	t_player	player;
	player = data->player_data;

	(void)player;
	if (orientation == 'E')
		player.angle = 0;
	else if (orientation == 'S')
		player.angle = M_PI_2;
	else if (orientation == 'W')
		player.angle = M_PI;
	else 
		player.angle = 3 * M_PI;
}

void	line_draw(struct s_position *pointA, struct s_position *pointB, mlx_image_t* y_img, char **map)
{
	double x;
	double y;
	double x1, y1;
	double x2, y2, dx, dy, step;
	int i;

	x1 = pointA->x_axis;
	y1 = pointA->y_axis;
	x2 = pointB->x_axis;
	y2 = pointB->y_axis;

	dx = (x2 - x1);
	dy = (y2 - y1);
	//do algorithm while hit is 0
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	x = x1;
	y = y1;
	i = 1;
	//check if hit a wall
	while (i <= step) {
		if (map[(int)y / TILE][(int)x / TILE] == '1')
			return ;
		else
		{
			mlx_put_pixel(y_img, x, y, 0xFAFABB);
			x = x + dx;
			y = y + dy;
			i = i + 1;
		}
	}
}

void	draw_fov(t_game **game_data)
{
//	double	delta_angle;
//	double	player_angle;
	struct s_position	*origin;
	struct s_position	*point;
	double				fov_angle;

	
	fov_angle = (*game_data)->player_data.angle;
//	player_angle = (*game_data)->player_data.angle;
//	delta_angle = 0.1;
	origin = &(*game_data)->player_data.current_position;
	point = &(*game_data)->player_data.end_position;
	update_origin(game_data);
	while (fov_angle < (*game_data)->player_data.angle + M_PI / 6)
	{
		line_draw(origin, point, (*game_data)->bg_img, (*game_data)->map_data->map_array);
		fov_angle += 0.005;
		update_end(game_data, fov_angle);
	}
	while (fov_angle > (*game_data)->player_data.angle - M_PI / 6)
	{
		line_draw(origin, point, (*game_data)->bg_img, (*game_data)->map_data->map_array);
		fov_angle -= 0.005;
		update_end(game_data, fov_angle);
	}
}
