
#include "cub3D.h"

int	get_color_texture(mlx_texture_t *tex, t_game *game_data, int topy)
{
	int position;
	int color;
	int	texture_x;
	int	texture_y;
	double x;
	double y;
	int	difference;
	double height;
	double new_angle;
	mlx_texture_t *north;
	mlx_texture_t *south;
	mlx_texture_t *west;
	mlx_texture_t *east;
	//int alpha;

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
	double fov_end = fmod(new_angle - (M_PI / 6), 2 * M_PI);
    double fov_start = fmod(new_angle + (M_PI / 6) , 2 * M_PI);
	if (difference < 0)
		topy += -difference;
	if (fov_end < 0)
        fov_end += 2 * M_PI;
	//alpha = 255 / pow(game_data->distance, 0.3) * 2;
		if ((int)y % TILE == 0)
		{
			if (((fov_end >= M_PI) || fov_start >= M_PI) ||  ((fov_end <= M_PI * 2 || fov_start >= 0) || (fov_start < M_PI / 6)))
			{
				//north
				texture_y = (topy) * ((double)north->height - 1) / height;  
				texture_x = fmod((x / TILE), 1.0) * north->width;
				position = (texture_y * north->width + texture_x) * north->bytes_per_pixel;
				color = get_rgba(north->pixels[position], north->pixels[position + 1], north->pixels[position + 2], north->pixels[position + 3]);
				return (color);
			}
		}
		if ((int)x % TILE == 0)
		{
			if ((fov_end < 3 * M_PI_2) || (fov_start > M_PI_2))
			{
			//west
				texture_x= (topy) * ((double)west->height - 1) / height;  
				texture_y = fmod((y / TILE), 1.0) * west->width;
				position = ((texture_x) * west->height + (west->width - 1 - texture_y)) * west->bytes_per_pixel;
				color = get_rgba(west->pixels[position], west->pixels[position + 1], west->pixels[position + 2], west->pixels[position + 3]);
				return (color);
			}
		}
		if ((int)y % TILE == 1)
		{
			if ((fov_end <= 3 * M_PI_2) || (fov_start >= 3 * M_PI_2) || (fov_end >= 0) || ((fov_start >= 0) && (fov_start > 11 * M_PI / 6)))
			{
				//south
				texture_y = (topy) * ((double)south->height - 1) / height;  
				texture_x = fmod((x / TILE), 1.0) * south->width;
				position = ((texture_y) * south->width + (south->width - 1 - texture_x)) * south->bytes_per_pixel;
				color = get_rgba(south->pixels[position], south->pixels[position + 1], south->pixels[position + 2], south->pixels[position + 3]);
				return (color);
			}
		}
		if ((int)x % TILE == 1)
		{
			if ((fov_start > 3 * M_PI_2 || fov_start < 2 * M_PI) || (fov_end < M_PI_2))
			{
				texture_y = (topy) * ((double)east->height - 1) / height;  
				texture_x = fmod((y / TILE), 1.0) * east->width;
				position = (texture_y * east->width + texture_x) * east->bytes_per_pixel;
				color = get_rgba(east->pixels[position], east->pixels[position + 1], east->pixels[position + 2], east->pixels[position + 3]);
				return (color);
			}
		}
	/*
	texture_y = (topy) * ((double)north->height - 1) / height;  
	texture_x = fmod((x / TILE), 1.0) * north->width;
	position = (texture_y * north->width + texture_x) * north->bytes_per_pixel;
	color = get_rgba(north->pixels[position], north->pixels[position + 1], north->pixels[position + 2], north->pixels[position + 3]);
	*/
	return (0xfafafa);
}

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

void	draw_wall(t_game **game_data, t_int_vector center, double fov)
{
	double	height;
	unsigned int x0;
	//unsigned int y0;
	int topy;
	//double	distance;
	int posy;
	int color;

	(*game_data)->distance *= (cos(M_PI / 6 - fov));
	height = WALL_HEIGHT / (*game_data)->distance;
	topy = SCREEN_HEIGHT / 2 - height / 2;
	if (topy < 0)
		topy = 0;
	x0 = center.x;
	//y0 = center.y - (height / 2);
	posy = topy;
	while (topy <= center.y + (height / 2) && topy <= SCREEN_HEIGHT)
	{
		while (x0 < center.x + 1)
		{
			color = get_color_texture((*game_data)->north, (*game_data), topy - posy);
			mlx_put_pixel((*game_data)->bg_img, x0++, topy, color);
		}
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
			game_data->distance = distance;
			game_data->player_data.end_ray.x_axis= x + 1;
			game_data->player_data.end_ray.y_axis= y + 1;
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
		draw_wall(game_data, center, fov_shit);
		fov_angle += DELTA_FOV;
		fov_shit += DELTA_FOV;
		center.x++;
	}
}
