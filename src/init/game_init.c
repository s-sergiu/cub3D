
#include "cub3D.h"

void	initialize_game_data(struct s_game **game_data,
							struct s_map *map_data)
{
	mlx_t*			mlx;
	mlx_image_t*	image;

	*game_data = (struct s_game *)malloc(sizeof(struct s_game));
	if (game_data == NULL)
		cleanup_and_exit(errno, 0, NULL);
	if (!(mlx = mlx_init(map_data->width, map_data->height, "cub3D", true)))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
	if (!(image = mlx_new_image(mlx, map_data->width, map_data->height)))
	{
		mlx_close_window(mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
	(*game_data)->mlx_handle = mlx;
	(*game_data)->mlx_background_image = image;
	(*game_data)->map_data = map_data;
	(*game_data)->player_data.player_image = NULL;
}

void	destroy_game_data(struct s_game **game_data)
{
	free((*game_data));
}
