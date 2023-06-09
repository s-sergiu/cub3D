
#include "cub3D.h"

void leak_check () {
	system("leaks cub3D");
}

int	main(int argc, char **argv)
{
	t_memory	*block;
	if( atexit(leak_check) != 0 ) {
			perror("Unable to set exit function\n");
			return EXIT_FAILURE;
	}
	block = NULL;
	if (argc != 2)
		write(1, "Usage: ./cub3D <map.cub>\n", 25);
	else
		if (is_valid_filename(argv[1]))
			game_setup(&block, argv[1]);
	free_all_memory_blocks(&block);
	return (0);
}
