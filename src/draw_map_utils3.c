#include "cub3D.h"

void	draw_ceiling(t_game **game_data)
{
	unsigned int	x0;
	unsigned int	y0;

	x0 = 0;
	y0 = -1;
	while (++y0 < SCREEN_HEIGHT / 2)
	{
		while (x0 < SCREEN_WIDTH)
			mlx_put_pixel((*game_data)->ceiling, x0++,
				y0, (*game_data)->ceiling_color);
		x0 = 0;
	}
}

void	draw_floor(t_game **game_data)
{
	unsigned int	x0;
	unsigned int	y0;

	x0 = 0;
	y0 = -1;
	while (++y0 < SCREEN_HEIGHT / 2)
	{
		while (x0 < SCREEN_WIDTH)
			mlx_put_pixel((*game_data)->floor, x0++,
				y0, (*game_data)->floor_color);
		x0 = 0;
	}
}

void	add_ceiling(t_game **game_data)
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	unsigned int	x0;
	unsigned int	y0;

	mlx = (*game_data)->mlx;
	create_img(&image, mlx, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
	(*game_data)->ceiling = image;
	x0 = 0;
	y0 = 0;
	place_image(image, mlx, x0, y0);
	set_img_color(image, 255);
}

void	add_floor(t_game **game_data)
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	unsigned int	x0;
	unsigned int	y0;

	mlx = (*game_data)->mlx;
	create_img(&image, mlx, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
	(*game_data)->floor = image;
	x0 = 0;
	y0 = SCREEN_HEIGHT / 2;
	place_image(image, mlx, x0, y0);
	set_img_color(image, 255);
}
