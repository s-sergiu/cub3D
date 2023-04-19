
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

void	initialize_map_data(struct s_map **map_data, char *map_file)
{
	char	*map_string;

	map_string = read_map(map_file);
	if (map_string == NULL)
		cleanup_and_exit(errno, 0, NULL);
	*map_data = (struct s_map *)malloc(sizeof(struct s_map));
	if (map_data == NULL)
		cleanup_and_exit(errno, 0, map_string);
	(*map_data)->map_string = map_string;
	(*map_data)->map_array = ft_split((*map_data)->map_string, '\n');
	if ((*map_data)->map_array == NULL)
    {
        free((*map_data)->map_string);
        free(*map_data);
		exit(errno);
    }
	(*map_data)->width = ft_strlen((*map_data)->map_array[0]) * TILE;
	(*map_data)->height = get_map_height((*map_data)->map_array) * TILE;
}

void	destroy_game_data(struct s_game **game_data)
{
	free((*game_data));
}

void	destroy_map_data(struct s_map **map_data)
{
	if ((*map_data)->map_string)
		free((*map_data)->map_string);
	if ((*map_data)->map_array)
		free_array_of_memory((*map_data)->map_array);
	free((*map_data));
}
