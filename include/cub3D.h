
#ifndef CUB3D_H
# define CUB3D_H

# include <assert.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include "libft.h"
# include "MLX42/MLX42.h"
# include "libarrtools.h"
# define TRUE 1
# define FALSE 0
# define TILE 64
# define EMPTY_MAP 254
# define IS_DIRECTORY 21
# define BAD_MAP_FILE 255
# define PLAYER 'P'
# define WALL '1'
# define SPEED 10.0
# define ANGLE_SPEED 0.07
# define DELTA_FOV 0.001
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define WALL_HEIGHT 25000

typedef struct s_game		t_game;
typedef struct s_player		t_player;
typedef struct s_map		t_map;
typedef struct s_vector		t_vector;
typedef struct s_int_vector	t_int_vector;

struct s_vector
{
	double	x;
	double	y;
};

struct s_int_vector
{
	int	x;
	int	y;
};

struct s_position
{
	double	x_axis;
	double	y_axis;
};

struct s_static_position
{
	double	x_axis;
	double	y_axis;
};

struct s_player
{
	struct s_static_position	initial_position;
	struct s_position			current_position;
	struct s_position			end_position;
	double						angle;
	mlx_image_t					*player_image;
};

struct s_game
{
	mlx_t					*mlx;
	mlx_image_t				*bg_img;
	mlx_image_t				*game_screen;
	mlx_image_t				*floor;
	mlx_image_t				*ceiling;
	mlx_image_t				*wall;
	double					width;
	int						height;
	int						n;
	struct s_map			*map_data;
	struct s_player			player_data;
};

struct s_map
{
	char	**map_array;
	int		height;
	int		width;
};

void		game_setup(char *argv);

/**
 * @brief Initializes map data.
 *
 * This function initializes a map_data struct and sets its map_string
 *	map_array, width, and height values.
 *
 * @param map_data A pointer to the map_data struct to be initialized.
 * @param map_file The file path of the map file to be read.
 */
void		init_map_data(t_map **map_data, char *map_file);

/**
 * @brief Destroys map data.
 *
 * This function frees memory allocated for a map_data struct and its 
 *	components.
 *
 * @param map_data A pointer to the map_data struct to be destroyed.
 */
void		destroy_map_data(t_map *map_data);

/**
 * @brief Prints an error message to the standard error output and exits 
 *	with the function parameter passed error code.
 *
 * @param error The error number to print.
 *
 * @return void.
 */
void		print_error(int error);

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
void		cleanup_and_exit(int error, int file, char *buffer);

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
char		*read_map(char *filename);

/**
 * @brief Checks if the given filename has a valid extension.
 *
 * This function checks if the extension of the given filename is ".cub".
 *
 * @param filename The filename to check.
 * @return Returns TRUE (1) if the extension is valid, and FALSE (0) otherwise.
 */
int			has_invalid_map_extension(char *filename);

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
int			is_valid_filename(char *filename);
void		protected_malloc(void **parameter, size_t size_of_parameter);
void		init_game_data(t_game **game_data,
				t_map *map_data);
void		destroy_game_data(t_game *game_data);
void		place_image(mlx_image_t *img, mlx_t *mlx, int width, int height);
void		create_img(mlx_image_t **img, mlx_t *mlx, int width, int height);
void		press_d(char **map, t_game *game_data);
void		press_a(char **map, t_game *game_data);
void		press_s(char **map, t_game *game_data);
void		press_w(char **map, t_game *game_data);
void		place_wall_or_player(char **map, t_game *game_data, int x, int y);
void		draw_grid(t_map *map_data, mlx_image_t *image);
void		set_img_color(mlx_image_t *img, uint32_t color_value);
void		draw_new_image(mlx_image_t **img, mlx_t *mlx, int x, int y);
void		draw_ray(t_game **game_data);
void		press_right(t_game **data);
void		press_left(t_game **data);
void		line_draw(struct s_position *pointA, struct s_position *pointB, mlx_image_t * y_img, char **map, t_game *game_data);
void	draw_fov(t_game **game_data);
void	update_origin(t_game **game_data);
void	update_end(t_game **game_data, double fov_angle);
void	draw_wall(t_game *game_data, t_int_vector center);
void	add_bg_image(t_game **game_data);

#endif
