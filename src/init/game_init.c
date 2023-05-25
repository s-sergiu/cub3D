
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

void	destroy_game_data(t_game *game_data)
{
	free(game_data);
}

void	init_game_data(t_game **game_data, t_map *map_data)
{
	mlx_t			*mlx;

	mlx = NULL;
	malloc_game_struct(game_data, *destroy_map_data, map_data);
	init_mlx(&mlx, 1920, 1080);
	if (!mlx)
	{
		destroy_game_data(*game_data);
		destroy_map_data(map_data);
		exit(errno);
	}
	(*game_data)->mlx = mlx;
	(*game_data)->bg_img = NULL;
	(*game_data)->wall = NULL;
	(*game_data)->game_screen = NULL;
	(*game_data)->floor = NULL;
	(*game_data)->ceiling = NULL;
	(*game_data)->map_data = map_data;
	(*game_data)->player_data.player_image = NULL;
	(*game_data)->player_data.angle = 3 * M_PI_2;
}
