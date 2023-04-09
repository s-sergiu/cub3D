
#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include "libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

typedef struct s_map_data t_map_data;

struct	s_map_data 
{
	char	**map;
	int		height;
	int		width;
};

char					*read_map(char *file);
struct s_map_data		*get_width_and_height(char **map);
void					draw_map(char **map);

#endif
