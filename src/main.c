
#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	struct s_map_data	*data;

	data = NULL;
	if (argc != 2)
		write(1, "usage: \n", 8);
	else
	{
		write(1, "success\n", 8);
		if (filename_is_valid(argv[1]))
		{
			write(1, "succes1\n", 8);
			init_map_data(&data, argv[1]);
		}
//			draw_map(data);
		if (data)
			destroy_map_data(&data);
	}
	return (0);
}
