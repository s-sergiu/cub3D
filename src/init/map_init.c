
#include "cub3D.h"

char	*try_read_map(char *map_file)
{
	char	*pointer;
	pointer = read_map(map_file);
	if (pointer == NULL)
		exit(errno);
	return (pointer);
}

char	**try_split_string(char *string, t_map *map_data)
{
	char **map_array;

	map_array = ft_split(string, '\n');
	if (map_array == NULL)
	{
        free(string);
		free(map_data);
		exit(errno);
	}
	free(string);
	return (map_array);
}

void	malloc_map_struct(t_map **map_data, void (*f)(void *), void *data)
{
	*map_data = (t_map *)malloc(sizeof(t_map));
	if (map_data == NULL)
	{
		f(data);
		exit(errno);
	}
}

void	destroy_map_data(t_map *map_data)
{
	if (map_data->map_array)
		arrtools_free(map_data->map_array);
	free(map_data);
}

void	init_map_data(t_map **map_data, char *map_file)
{
	char	*map_string;

	map_string = try_read_map(map_file);
	malloc_map_struct(map_data, free, map_string);
	(*map_data)->map_array = try_split_string(map_string, *map_data);
	(*map_data)->width = ft_strlen((*map_data)->map_array[0]) * TILE;
	(*map_data)->height = arrtools_arrlen((*map_data)->map_array) * TILE;
}
