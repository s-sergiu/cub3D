
#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	struct s_map_data	*data;

	data = NULL;
	if (argc != 2)
		write(1, "Usage: ./cub3D <map.cub>\n", 25);
	else
	{
		if (filename_is_valid(argv[1]))
		{
			init_map_data(&data, argv[1]);
			draw_map(data);
		}
		if (data)
			destroy_map_data(&data);
	}
	return (0);
}
