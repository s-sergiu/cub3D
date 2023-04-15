
#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <assert.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include "libft/libft.h"
# include "../external/MLX42/include/MLX42/MLX42.h"
# define TRUE 1
# define FALSE 0
# define TILE 64
# define EMPTY_MAP 254
# define IS_DIRECTORY 21
# define BAD_MAP_FILE 255

typedef struct s_map_data	t_map_data;

struct s_map_data
{
	char	*map_string;
	char	**map_array;
	int		height;
	int		width;
};

void			draw_map(struct s_map_data *data);

/**
 * @brief Initializes map data.
 *
 * This function initializes a map_data struct and sets its map_string
 *	map_array, width, and height values.
 *
 * @param data A pointer to the map_data struct to be initialized.
 * @param map_file The file path of the map file to be read.
 */
void			initialise_map_data(struct s_map_data **data, char *map_file);

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
 * @brief Prints an error message to the standard error output and exits 
 *	with the function parameter passed error code.
 *
 * @param error The error number to print.
 *
 * @return void.
 */
void			print_error(int error);

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
 * @param string_array The string array to be freed.
 */
void			free_array_of_memory(char **string_array);

/**
 * @brief Gets the height of a map.
 *
 * This function takes a 2D string array representing a map and returns its 
 *	height.
 *
 * @param map_array The 2D string array representing the map.
 * @return The height of the map.
 */
int				get_map_height(char **map_array);

/**
 * @brief Checks if the given filename has a valid extension.
 *
 * This function checks if the extension of the given filename is ".cub".
 *
 * @param filename The filename to check.
 * @return Returns TRUE (1) if the extension is valid, and FALSE (0) otherwise.
 */
int				has_invalid_map_extension(char *filename);

 /**
 * @brief Checks if the given filename is valid.
 *
 * This function checks if the extension of the given filename is valid.
 * If the extension is not valid, it calls the handle_error() function with 
 *	the error code BAD_MAP_FILE.
 *
 * @param filename The filename to check.
 * @return Returns TRUE (1) if the filename is valid, and the handle_error() 
 *	function does not return an error code. Otherwise, it returns FALSE (0).
 */
int				is_valid_filename(char *filename);

#endif
