#include "cub3D.h"

void	malloc_game_struct(t_memory **block, t_game **game_data)
{
	(*game_data) = malloc_to_block(block, sizeof(struct s_game));
	if ((*game_data) == NULL)
	{
		free_all_memory_blocks(block);
		printf("Error initializing game data struct\n");
		exit(1);
	}
}

void	init_mlx(mlx_t **mlx, int width, int height)
{
	(*mlx) = mlx_init(width, height, "cub3D", true);
	if (!mlx)
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
}

void	init_game_data_values(t_game **game_data, mlx_t *mlx)
{
	(*game_data)->n = (((M_PI / 3) / DELTA_FOV));
	(*game_data)->mlx = mlx;
	(*game_data)->ceiling_color = 0;
	(*game_data)->floor_color = 0;
	(*game_data)->color[0] = 0;
	(*game_data)->color[1] = 0;
	(*game_data)->color[2] = 0;
	(*game_data)->color[3] = 0;
	(*game_data)->north = NULL;
	(*game_data)->south = NULL;
	(*game_data)->east = NULL;
	(*game_data)->west = NULL;
	(*game_data)->bg_img = NULL;
	(*game_data)->game_screen = NULL;
	(*game_data)->floor = NULL;
	(*game_data)->ceiling = NULL;
	(*game_data)->player_data.player_image = NULL;
	(*game_data)->distance = 8;
}

void	init_game_data(t_memory **block, t_game **game_data)
{
	mlx_t			*mlx;

	mlx = NULL;
	malloc_game_struct(block, game_data);
	init_mlx(&mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!mlx)
	{
		free_all_memory_blocks(block);
		printf("Error initializing mlx engine\n");
		exit(1);
	}
	init_game_data_values(game_data, mlx);
}
