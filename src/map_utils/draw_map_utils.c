
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

/*
	init_map_data:
	Initializes the s_map_data structure;
*/

int	init_map_data(struct s_map_data **data, char *map_file)
{
	(*data) = malloc(sizeof(struct s_map_data));
	if (!(*data))
		return (FALSE);
	(*data)->map_string = read_map(map_file);
	if ((*data)->map_string == NULL)
		return (FALSE);
	if ((*data)->map_string)
	{
		(*data)->map = ft_split((*data)->map_string, '\n');
		(*data)->width = ft_strlen((*data)->map[0]) * 32;
		(*data)->height = get_height((*data)->map) * 32;
	}
	return (TRUE);	
}

/*
	destroy_map_data:
	Destroys the s_map_data structure;
*/

void	destroy_map_data(struct s_map_data **data)
{
	free((*data)->map_string);
	if ((*data)->map_string)
		if ((*data)->map)
			free_split((*data)->map);
	free((*data));
}
