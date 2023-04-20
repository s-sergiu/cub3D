
#include "cub3D.h"

char	*try_read_map(char *map_file)
{
	char	*pointer;
	pointer = read_map(map_file);
	if (pointer == NULL)
		exit(errno);
	return (pointer);
}

char	**try_split_string(char *string, struct s_map *map_data)
{
	char **map_array;

	map_array = ft_split(map_string, '\n');
	if (map_array == NULL)
	{
        free(map_string);
		free(map_data);
		exit(errno);
	}
	return (map_array);
}

void	init_map_data(struct s_map **map_data, char *map_file)
{
	char	*map_string;

	map_string = try_read_map(map_file);
	*map_data = (struct s_map *)malloc(sizeof(struct s_map));
	if (map_data == NULL)
		cleanup_and_exit(errno, 0, map_string);
	(*map_data)->map_array = try_split_string(map_string, map_data);
	(*map_data)->width = ft_strlen((*map_data)->map_array[0]) * TILE;
	(*map_data)->height = arrtools_arrlen((*map_data)->map_array) * TILE;
}

void	destroy_map_data(struct s_map **map_data)
{
	if ((*map_data)->map_string)
		free((*map_data)->map_string);
	if ((*map_data)->map_array)
		arrtools_free((*map_data)->map_array);
	free((*map_data));
}
