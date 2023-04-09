
#include "../include/cub3D.h"

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

struct s_map_data	*get_width_and_height(char **map)
{
	struct s_map_data	*data;

	data = malloc(sizeof(struct s_map_data));
	data->width = ft_strlen(map[0]) * 32;
	data->height = get_height(map) * 32;
	printf("Width: %d\n", data->width);
	printf("Height: %d\n", data->height);
	printf("Area: %d\n", data->height * data->width);
	return (data);
}
