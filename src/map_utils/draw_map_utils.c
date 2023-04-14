
#include "../../include/map_utils/map_utils.h"

void	free_split(char **str)
{
	int	i;	

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	init_map_data(struct s_map_data **data, char *map_file)
{
	char	*map;

	map = read_map(map_file);
	(*data) = malloc(sizeof(struct s_map_data));
	if (!(*data))
		handle_error(errno);
	(*data)->map_string = map;
	if ((*data)->map_string == NULL)
		cleanup_and_exit(errno, 0, NULL);
	if ((*data)->map_string)
	{
		(*data)->map = ft_split((*data)->map_string, '\n');
		(*data)->width = ft_strlen((*data)->map[0]) * TILE;
		(*data)->height = get_height((*data)->map) * TILE;
	}
}

void	destroy_map_data(struct s_map_data **data)
{
	free((*data)->map_string);
	if ((*data)->map_string)
		if ((*data)->map)
			free_split((*data)->map);
	free((*data));
}
