
#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	char *map;

	(void)argc;
	(void)argv;
	if (argc != 2)
		write(1, "usage: \n", 8);
	else
	{
		write(1, "success\n", 8);
		map = read_map(argv[1]);
		printf("map: %s\n", map);
	}
	free(map);
	return (0);
}
