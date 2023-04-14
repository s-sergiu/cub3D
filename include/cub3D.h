
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
# define TILE 64
# define EMPTY_MAP 254
# define BAD_MAP_FILE 255

typedef struct s_map_data	t_map_data;

struct s_map_data
{
	char	*map_string;
	char	**map;
	int		height;
	int		width;
};

void			draw_map(struct s_map_data *data);

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

/**
 * @brief Prints an error message to the standard error output.
 *
 * @param error The error number to print.
 *
 * @return void.
 */
void			print_error(int error);

/**
 * @brief Handles the given error number, prints an error message to the 
 *	standard error output, and exits the program.
 *
 * @param error The error number to handle.
 *
 * @return void.
 */
int				handle_error(int error);

/**
 * @brief Frees any allocated memory and exits the program with the given 
 *	error number.
 *
 * @param error The error number to print.
 * @param file The file descriptor to close.
 * @param buffer The buffer to free.
 *
 * @return void.
 */
void			cleanup_and_exit(int error, int file, char *buffer);

/**
 * @brief Returns the total number of bytes in the file with the given 
 *	filename.
 *
 * @param filename The name of the file.
 *
 * @return The total number of bytes in the file.
 */
int				get_total_bytes(char *filename);

/**
 * @brief Reads the contents of the file with the given name into a 
 *	dynamically allocated buffer.
 *
 * @param file The name of the file.
 *
 * @return A pointer to the dynamically allocated buffer containing the file 
 *	contents, or NULL on error.
 */
char			*read_map(char *filename);

/**
 * @brief Frees memory allocated for a string array.
 *
 * This function frees the memory that was allocated for a string array.
 *
 * @param str The string array to be freed.
 */
void			free_split(char **str);

/**
 * @brief Gets the height of a map.
 *
 * This function takes a 2D string array representing a map and returns its 
 *	height.
 *
 * @param map The 2D string array representing the map.
 * @return The height of the map.
 */
int				get_height(char **map);

#endif
