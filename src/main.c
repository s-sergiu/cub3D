
#include "cub3D.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		write(1, "Usage: ./cub3D <map.cub>\n", 25);
	else
		if (is_valid_filename(argv[1]))
			game_setup(argv[1]);
	return (0);
}
