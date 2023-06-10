#include "cub3D.h"

void	draw_horizontal_line(int height, int width, mlx_image_t *image)
{
	int	x;
	int	y;

	x = 0;
	y = TILE;
	while (y < height)
	{
		while (x < width)
			mlx_put_pixel(image, x++, y, 0xFAFAFA);
		y += TILE;
		x = 0;
	}
}

void	draw_vertical_line(int height, int width, mlx_image_t *image)
{
	int	x;
	int	y;

	y = 0;
	x = TILE;
	while (x < width)
	{
		while (y < height)
			mlx_put_pixel(image, x, y++, 0xFAFAFA);
		x += TILE;
		y = 0;
	}
}

void	draw_grid(t_map *map_data, mlx_image_t *image)
{
	int	height;
	int	width;

	height = map_data->height;
	width = map_data->width;
	draw_horizontal_line(height, width, image);
	draw_vertical_line(height, width, image);
}

void	change_empty_space(t_map **map_data, int i, int j)
{
	(*map_data)->map_copy[i][j] = '1';
	(*map_data)->map[i][j] = '1';
}
