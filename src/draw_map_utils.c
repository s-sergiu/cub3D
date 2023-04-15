
#include "../include/cub3D.h"

void	free_array_of_memory(char **string_array)
{
	int	index;	

	index = -1;
	while (string_array[++index])
		free(string_array[index]);
	free(string_array);
}

int	get_height(char **map_array)
{
	int	index;

	index = 0;
	while (map_array[index])
		index++;
	return (index);
}

void	initialise_map_data(struct s_map_data **data, char *map_file)
{
	char	*map_string;

	map_string = read_map(map_file);
	(*data) = malloc(sizeof(struct s_map_data));
	if (data == NULL)
		handle_error(errno);
	(*data)->map_string = map_string;
	if ((*data)->map_string == NULL)
		cleanup_and_exit(errno, 0, NULL);
	if ((*data)->map_string)
	{
		(*data)->map_array = ft_split((*data)->map_string, '\n');
		(*data)->width = ft_strlen((*data)->map_array[0]) * TILE;
		(*data)->height = get_height((*data)->map_array) * TILE;
	}
}

void	destroy_map_data(struct s_map_data **data)
{
	free((*data)->map_string);
	if ((*data)->map_string)
		if ((*data)->map_array)
			free_array_of_memory((*data)->map_array);
	free((*data));
}
