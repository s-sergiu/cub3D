
#include "../include/cub3D.h"

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	get_width_and_height(char **map)
{
	int	width;
	int	height;

	width = ft_strlen(map[0]);
	height = get_height(map);
	printf("Width: %d\n", width);
	printf("Height: %d\n", height);
	printf("Area: %d\n", height * width);
}
