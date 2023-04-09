
#include "../include/cub3D.h"

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
	(*data) = malloc(sizeof(struct s_map_data));
	(*data)->map_string = read_map(map_file);
	printf("map string %s\n", (*data)->map_string);
	if ((*data)->map_string != NULL)
	{
		(*data)->map = ft_split((*data)->map_string, '\n');
		(*data)->width = ft_strlen((*data)->map[0]) * 32;
		(*data)->height = get_height((*data)->map) * 32;
	}
	
}

void	destroy_map_data(struct s_map_data **data)
{
	free((*data)->map_string);
	if ((*data)->map_string != NULL)
		free_split((*data)->map);
	free((*data));
}
