
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

char		*read_map(char *file);
void		get_width_and_height(char **map);

#endif
