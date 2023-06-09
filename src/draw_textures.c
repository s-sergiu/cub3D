#include "cub3D.h"

int	return_north_texture(t_game **game_data, int topy)
{
	int				position;
	int				color;
	mlx_texture_t	*north;
	int				texture_y;
	int				texture_x;

	north = (*game_data)->north;
	texture_y = (topy) * ((double)north->height - 1) / (WALL_HEIGHT
			/ (*game_data)->distance);
	texture_x = fmod(((*game_data)->player_data.end_ray.x_axis / TILE), 1.0)
		* north->width;
	position = (texture_y * north->width + texture_x)
		* north->bytes_per_pixel;
	color = get_rgba(north->pixels[position],
			north->pixels[position + 1], north->pixels[position + 2],
			north->pixels[position + 3]);
	return (color);
}

int	return_west_texture(t_game **game_data, int topy)
{
	int				position;
	int				color;
	mlx_texture_t	*west;
	int				texture_y;
	int				texture_x;

	west = (*game_data)->west;
	texture_y = (topy) * ((double)west->height - 1) / (WALL_HEIGHT
			/ (*game_data)->distance);
	texture_x = fmod(((*game_data)->player_data.end_ray.y_axis / TILE), 1.0)
		* west->width;
	position = (texture_y * west->width + texture_x)
		* west->bytes_per_pixel;
	color = get_rgba(west->pixels[position],
			west->pixels[position + 1], west->pixels[position + 2],
			west->pixels[position + 3]);
	return (color);
}

int	return_south_texture(t_game **game_data, int topy)
{
	int				position;
	int				color;
	mlx_texture_t	*south;
	int				texture_y;
	int				texture_x;

	south = (*game_data)->south;
	texture_y = (topy) * ((double)south->height - 1) / (WALL_HEIGHT
			/ (*game_data)->distance);
	texture_x = fmod((((*game_data)->player_data.end_ray.x_axis) / TILE), 1.0)
		* south->width;
	position = ((texture_y) * south->width
			+ (south->width - 1 - texture_x)) * south->bytes_per_pixel;
	color = get_rgba(south->pixels[position],
			south->pixels[position + 1], south->pixels[position + 2],
			south->pixels[position + 3]);
	return (color);
}

int	return_east_texture(t_game **game_data, int topy)
{
	int				position;
	int				color;
	mlx_texture_t	*east;
	int				texture_y;
	int				texture_x;

	east = (*game_data)->east;
	texture_y = (topy) * ((double)east->height - 1) / (WALL_HEIGHT
			/ (*game_data)->distance);
	texture_x = fmod(((*game_data)->player_data.end_ray.y_axis / TILE), 1.0)
		* east->width;
	position = (texture_y * east->width + texture_x)
		* east->bytes_per_pixel;
	color = get_rgba(east->pixels[position],
			east->pixels[position + 1], east->pixels[position + 2],
			east->pixels[position + 3]);
	return (color);
}
