
#include <cub3D.h>

int	main(int argc, char **argv)
{
	struct s_map_data	*map_data;

	map_data = NULL;
	if (argc != 2)
		write(1, "Usage: ./cub3D <map.cub>\n", 25);
	else
	{
		if (is_valid_filename(argv[1]))
		{
			initialize_map_data(&map_data, argv[1]);
			draw_map(map_data);
		}
		if (map_data)
			destroy_map_data(&map_data);
	}
	return (0);
}
