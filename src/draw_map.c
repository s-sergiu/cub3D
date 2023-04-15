
#include "../include/cub3D.h"

mlx_image_t*	player;

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		printf("player y: %d\n", player->instances[0].y / TILE);
		printf("player x: %d\n", player->instances[0].x / TILE);
		player->instances[0].y -= 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		player->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		player->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		player->instances[0].x += 5;
}

void	draw_walls(mlx_t *mlx, struct s_map_data *map_data)
{
	mlx_image_t*	img;
	int			x;
	int			y;
	int			i;
	int			j;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	while (map_data->map_array[i])
	{
		while (map_data->map_array[i][j])
		{
			if (map_data->map_array[i][j] == '1')
			{
				img = mlx_new_image(mlx, TILE, TILE);
				mlx_image_to_window(mlx, img, x, y);
				memset(img->pixels, 120, TILE * TILE * 4);
			}
			printf("%c", map_data->map_array[i][j]);
			j++;
			x += TILE;
		}
		printf("\n");
		i++;
		y += TILE;
		j = 0;
		x = 0;
	}
}

void	draw_player(mlx_t *mlx)
{
	player = mlx_new_image(mlx, 5, 5);
	mlx_image_to_window(mlx, player, 20, 20);
	for (uint32_t z = 0; z < player->width; ++z)
	{
		for (uint32_t b = 0; b < player->height; ++b)
		{
			mlx_put_pixel(player, z, b, 240);
		}
	}
}

void	draw_grid(struct s_map_data *map_data, mlx_image_t *image)
{
	int	x;
	int	y;

	x = 0;
	y = TILE;
	while (y < map_data->height)
	{
		while (x < map_data->width)
			mlx_put_pixel(image, x++, y, 231);
		y += TILE;
		x = 0;
	}
	y = 0;
	while (x < map_data->width)
	{
		while (y < map_data->height)
			mlx_put_pixel(image, x, y++, 255);
		x += TILE;
		y = 0;
	}
}

void	draw_map(struct s_map_data *map_data)
{
	mlx_t*				mlx;
	mlx_image_t*		image;

	if (!(mlx = mlx_init(map_data->width, map_data->height, "MLX42", true)))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
	if (!(image = mlx_new_image(mlx, map_data->width, map_data->height)))
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
	if (image != NULL)
		memset(image->pixels, 255, map_data->width * map_data->height * 4);
	//draw grid
	draw_grid(map_data, image);
	//draw walls
	draw_walls(mlx, map_data);
	//draw player
	draw_player(mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
