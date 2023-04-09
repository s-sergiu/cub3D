
#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (argc != 2)
		write(1, "usage: \n", 8);
	else
	{
		write(1, "success\n", 8);
		printf("bytes: %d\n", (get_total_bytes(argv[1])));
	}
	return (0);
}
