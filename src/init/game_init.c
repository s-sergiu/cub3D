
#include "cub3D.h"

void	malloc_game_struct(t_game **game_data, void (*f)(t_map *), void *data)
{
	*game_data = (t_game *)malloc(sizeof(struct s_game));
	if (game_data == NULL)
	{
		f(data);
		exit(errno);
	}
}

void	init_mlx(mlx_t **mlx, int width, int height)
{
	(*mlx) = mlx_init(width, height, "cub3D", true);
	if (!mlx)
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
}

void	create_img(mlx_image_t **img, mlx_t *mlx, int width, int height)
{
	(*img) = mlx_new_image(mlx, width, height);
	if (!img)
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
}

void	destroy_game_data(t_game *game_data)
{
	free(game_data);
}

void	init_game_data(t_game **game_data, t_map *map_data)
{
	mlx_t			*mlx;
	mlx_image_t		*background;
	int				width;
	int				height;

	width = map_data->width;
	height = map_data->height;
	mlx = NULL;
	background = NULL;
	malloc_game_struct(game_data, *destroy_map_data, map_data);
	init_mlx(&mlx, width, height);
	create_img(&background, mlx, width, height);
	if (!background || !mlx)
	{
		destroy_game_data(*game_data);
		destroy_map_data(map_data);
		exit(errno);
	}
	(*game_data)->mlx_handle = mlx;
	(*game_data)->mlx_background_image = background;
	(*game_data)->map_data = map_data;
	(*game_data)->player_data.player_image = NULL;
}
