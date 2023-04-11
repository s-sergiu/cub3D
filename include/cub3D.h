
#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "../external/MLX42/include/MLX42/MLX42.h"
# define TRUE 1
# define FALSE 0

typedef struct s_map_data t_map_data;

struct	s_map_data 
{
	char	*map_string;
	char	**map;
	int		height;
	int		width;
};

void					draw_map(struct s_map_data *data);
int						init_map_data(struct s_map_data **data, char *map_file);
void					destroy_map_data(struct s_map_data **data);
int						filename_is_valid(char *filename);

#endif
