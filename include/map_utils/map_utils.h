
#ifndef MAP_UTILS_H
# define MAP_UTILS_H

# include "../cub3D.h"
# include "../libft/libft.h"

# define EMPTY_MAP 254
# define BAD_MAP_FILE 255

/**
 * @brief Prints an error message to the standard error output.
 *
 * @param error_number The error number to print.
 *
 * @return void.
 */
void		print_error(int error_number);

/**
 * @brief Handles the given error number, prints an error message to the 
 *	standard error output, and exits the program.
 *
 * @param error_number The error number to handle.
 *
 * @return void.
 */
int			handle_error(int error_number);

/**
 * @brief Frees any allocated memory and exits the program with the given 
 *	error number.
 *
 * @param error_number The error number to print.
 * @param fd The file descriptor to close.
 * @param buffer The buffer to free.
 *
 * @return void.
 */
void		cleanup_and_exit(int error_number, int fd, char *buffer);

/**
 * @brief Returns the total number of bytes in the file with the given 
 *	filename.
 *
 * @param filename The name of the file.
 *
 * @return The total number of bytes in the file.
 */
int			get_total_bytes(char *filename);

/**
 * @brief Reads the contents of the file with the given name into a 
 *	dynamically allocated buffer.
 *
 * @param file The name of the file.
 *
 * @return A pointer to the dynamically allocated buffer containing the file 
 *	contents, or NULL on error.
 */
char		*read_map(char *file);

/**
 * @brief Frees memory allocated for a string array.
 *
 * This function frees the memory that was allocated for a string array.
 *
 * @param str The string array to be freed.
 */
void		free_split(char **str);

/**
 * @brief Gets the height of a map.
 *
 * This function takes a 2D string array representing a map and returns its 
 *	height.
 *
 * @param map The 2D string array representing the map.
 * @return The height of the map.
 */
int			get_height(char **map);

#endif
