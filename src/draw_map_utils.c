
#include "cub3D.h"
int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int get_rgba_a(char r, char g, char b, char a, double distance)
{
	if (distance < 0)
		distance = 1;
	r = 255 / distance;
	g = 255 / distance;
	b = 255 / distance;
	a = 255;
    return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_wall(t_game *game_data, t_int_vector center, double fov)
{
	double	height;
	unsigned int x0;
	//unsigned int y0;
	int topy;
	int color;
	int alpha;
	double	distance;

	distance = game_data->distance;
	// this is the formulae
	if (distance >= TILE / 2)
		distance *= (cos(M_PI / 6 - fov));
	height = WALL_HEIGHT / distance;
	topy = SCREEN_HEIGHT / 2 - height / 2;
	if (topy < 0)
		topy = 0;
	x0 = center.x;
	//y0 = center.y - (height / 2);
	//alpha = 255 / pow(distance, 0.3) * 2;
	(void)alpha;
	color = get_rgba(0, 255, 0, 255);
	while (topy <= center.y + (height / 2) && topy <= SCREEN_HEIGHT)
	{
		while (x0 < center.x + 2)
			mlx_put_pixel(game_data->bg_img, x0++, topy, color);
		x0 = center.x;
		topy++;
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
	double	distance;

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
	i = -1;
	//check if hit a wall
	while (++i <= step) {
		if (map[(int)(y / TILE)][(int)(x / TILE)] == '1')
		{
			//draw the wall from origin to x and y;
			distance = sqrt(pow(x1 - x, 2) + pow(y1 - y, 2));
			if (distance < TILE / 2)
				game_data->distance = 22;
			else
				game_data->distance = distance;
			return ;
		}
		else
			mlx_put_pixel(y_img, x = x + dx, y = y + dy, 0xFAFAFA);
	}
}

void	draw_fov(t_game **game_data)
{
	struct s_position	*origin;
	struct s_position	*point;
	double				fov_angle;
	double				fov_shit;
	t_int_vector		center;
	
	center = (t_int_vector) {0 , SCREEN_HEIGHT / 2};
	fov_angle = (*game_data)->player_data.angle - M_PI / 6;
	fov_shit = 0;
	origin = &(*game_data)->player_data.current_position;
	point = &(*game_data)->player_data.end_position;
	update_origin(game_data);
	while (fov_angle < (*game_data)->player_data.angle + M_PI / 6)
	{
		update_end(game_data, fov_angle);
		line_draw(origin, point, (*game_data)->bg_img, (*game_data)->map_data->map_array, (*game_data));
		draw_wall((*game_data), center, fov_shit);
		fov_angle += DELTA_FOV;
		fov_shit += DELTA_FOV;
		//center.x += SCREEN_WIDTH / ((((M_PI / 3) / DELTA_FOV)));
		center.x++;
	}
}
