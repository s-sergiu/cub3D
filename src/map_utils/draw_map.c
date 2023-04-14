
#include "../../include/map_utils/map_utils.h"

mlx_image_t*	player;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		player->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		player->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		player->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		player->instances[0].x += 5;
}

void	draw_map(struct s_map_data *data)
{
	mlx_image_t*	image;
	mlx_image_t*	img;
	mlx_t*			mlx;
	int			x;
	int			y;
	int			i;
	int			j;

	if (!(mlx = mlx_init(data->width, data->height, "MLX42", true)))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
	if (!(image = mlx_new_image(mlx, data->width, data->height)))
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
	memset(image->pixels, 255, data->width * data->height * 4);
	//draw grid
	x = 0;
	y = TILE;
	while (y < data->height)
	{
		while (x < data->width)
			mlx_put_pixel(image, x++, y, 231);
		y += TILE;
		x = 0;
	}
	y = 0;
	while (x < data->width)
	{
		while (y < data->height)
			mlx_put_pixel(image, x, y++, 255);
		x += TILE;
		y = 0;
	}
	//draw walls
	i = 0;
	j = 0;
	x = 0;
	y = 0;
	while (data->map[i])
	{
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
			{
				img = mlx_new_image(mlx, TILE, TILE);
				mlx_image_to_window(mlx, img, x, y);
				memset(img->pixels, 120, TILE * TILE * 4);
			}
			printf("%c", data->map[i][j]);
			j++;
			x += TILE;
		}
		printf("\n");
		i++;
		y += TILE;
		j = 0;
		x = 0;
	}
	//draw player
	player = mlx_new_image(mlx, 5, 5);
	mlx_image_to_window(mlx, player, 20, 20);
	for (uint32_t z = 0; z < player->width; ++z)
	{
		for (uint32_t b = 0; b < player->height; ++b)
		{
			mlx_put_pixel(player, z, b, 240);
		}
	}
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
