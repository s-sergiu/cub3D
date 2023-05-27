
#include "cub3D.h"

void	draw_wall(t_game *game_data, t_int_vector center)
{
	int	height;
	int	width;
	unsigned int x0;
	unsigned int y0;

	height = game_data->height;
	width = ceil(SCREEN_WIDTH / ceil(((M_PI / 3) / DELTA_FOV)));
	printf("insidneidne  %d\n", width);
	printf("insidneidne  %d\n", SCREEN_WIDTH);
	x0 = center.x - ceil(width / 2);
	y0 = center.y - (height / 2);
	while (y0 < center.y + (height / 2))
	{
		while (x0 < center.x + ceil(width / 2))
		{
			mlx_put_pixel(game_data->bg_img, x0 , y0, 0xFAFAFA);
			x0++;
		}
		x0 = center.x - ceil(width / 2);
		y0++;
	}
}

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

void	line_draw(struct s_position *pointA, struct s_position *pointB, mlx_image_t* y_img, char **map, t_game *game_data)
{
	double x;
	double y;
	double x1, y1;
	double x2, y2, dx, dy, step;
	int i;
	int	distance;

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
		{
			//draw the wall from origin to x and y;
			distance = sqrt(pow(x1 - x, 2) + pow(y1 - y, 2));
			if (distance == 0)
				game_data->height = WALL_HEIGHT;
			else
				game_data->height = WALL_HEIGHT / distance;
			//printf("distance %d\n", distance);
			game_data->width = SCREEN_WIDTH / ceil((((M_PI / 3) / DELTA_FOV)));
			if (game_data->height < 0)
				game_data->height = 100;
			return ;
		}
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
	struct s_position	*origin;
	struct s_position	*point;
	double				fov_angle;
	t_int_vector		center;

	
	center = (t_int_vector) {0 + (*game_data)->width / 2, SCREEN_HEIGHT / 2};
	printf("rays %f\n", ceil(((M_PI / 3) / DELTA_FOV)));
	printf("debug %d\n", (*game_data)->width );
	fov_angle = (*game_data)->player_data.angle - M_PI / 6;
	origin = &(*game_data)->player_data.current_position;
	point = &(*game_data)->player_data.end_position;
	update_origin(game_data);
	while (fov_angle < (*game_data)->player_data.angle + M_PI / 6)
	{
		line_draw(origin, point, (*game_data)->bg_img, (*game_data)->map_data->map_array, (*game_data));
		draw_wall((*game_data), center);
		center.x += (*game_data)->width;
		fov_angle += DELTA_FOV;
		update_end(game_data, fov_angle);
	}
}
