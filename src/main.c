
#include "../include/cub3D.h"

void	free_split(char **str)
{
	int	i;	

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	main(int argc, char **argv)
{
	char *map_string;
	char **map;

	(void)argc;
	(void)argv;
	if (argc != 2)
		write(1, "usage: \n", 8);
	else
	{
		write(1, "success\n", 8);
		map_string = read_map(argv[1]);
		printf("map string: %s\n", map_string);
		if (map_string)
		{
			map = ft_split(map_string, '\n');
			get_width_and_height(map);
			free_split(map);
		}
		free(map_string);
	}
	return (0);
}
