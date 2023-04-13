
#ifndef MAP_UTILS_H
# define MAP_UTILS_H

# include "../cub3D.h"
# include "../libft/libft.h"

# define EMPTY_MAP 254
# define BAD_MAP_FILE 255

char			*read_map(char *file);
int				handle_error(int error_number);
void			cleanup_and_exit(int error_number, int fd, char *buffer);
void			print_error(int error_number);

#endif
