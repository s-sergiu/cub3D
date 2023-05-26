
#include "cub3D.h"

void	draw_wall(mlx_image_t **img, t_game *game_data, int x)
{
	int y;
	int	width;
	int	height;

	width = game_data->width;
	height = game_data->height;
	(*img) = mlx_new_image(game_data->mlx, width, height);
	y = (SCREEN_WIDTH / 2) - (height / 2);
	place_image((*img), game_data->mlx, x, y);
	set_img_color((*img), 200);
	printf("address1 : %p\n", (*img));
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
			game_data->width = SCREEN_WIDTH / (((M_PI / 3) / DELTA_FOV));
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
//	double	delta_angle;
//	double	player_angle;
	struct s_position	*origin;
	struct s_position	*point;
	int x;
	int	width;
	double				fov_angle;
	int					i;

	
	width = (*game_data)->width;
	x = (SCREEN_HEIGHT / 2) - (width / 2);
	fov_angle = (*game_data)->player_data.angle;
//	player_angle = (*game_data)->player_data.angle;
//	delta_angle = 0.1;
	origin = &(*game_data)->player_data.current_position;
	point = &(*game_data)->player_data.end_position;
	update_origin(game_data);
	i = -1;
	while (fov_angle < (*game_data)->player_data.angle + M_PI / 6)
	{
		line_draw(origin, point, (*game_data)->bg_img, (*game_data)->map_data->map_array, (*game_data));
		draw_wall(&(*game_data)->rays[++i], (*game_data), x);
		printf("address2 : %p\n", (*game_data)->rays[i]);
		printf("x: %d\n", x);
		x += width;
		fov_angle += DELTA_FOV;
		update_end(game_data, fov_angle);
	}
	while (fov_angle > (*game_data)->player_data.angle - M_PI / 6)
	{
		line_draw(origin, point, (*game_data)->bg_img, (*game_data)->map_data->map_array, (*game_data));
		draw_wall(&(*game_data)->rays[++i], (*game_data), x);
		x -= width;
		fov_angle -= DELTA_FOV;
		update_end(game_data, fov_angle);
	}
}
