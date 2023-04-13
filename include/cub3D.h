
#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
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

/**
 * @brief Checks if the given filename is valid and ends with ".cub".
 *
 * @param filename The filename to check.
 *
 * @return TRUE (1) if the filename is valid, FALSE (0) otherwise.
 */
int filename_is_valid(char *filename);

/**
 * @brief Initializes map data.
 *
 * This function initializes a map_data struct and sets its map_string, width, 
 *	and height values.
 *
 * @param data A pointer to the map_data struct to be initialized.
 * @param map_file The file path of the map file to be read.
 */
void			init_map_data(struct s_map_data **data, char *map_file);

/**
 * @brief Destroys map data.
 *
 * This function frees memory allocated for a map_data struct and its 
 *	components.
 *
 * @param data A pointer to the map_data struct to be destroyed.
 */
void			destroy_map_data(struct s_map_data **data);

#endif
