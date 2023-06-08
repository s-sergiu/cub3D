#ifndef CUB3D_H
# define CUB3D_H

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
# define TILE 32
# define EMPTY_MAP 254
# define IS_DIRECTORY 21
# define BAD_MAP_FILE 255
# define PLAYER 'P'
# define WALL '1'
# define SPEED 10.0
# define ANGLE_SPEED 0.07
# define DELTA_FOV 0.0005
# define SCREEN_WIDTH 2096
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
	unsigned int	x;
	unsigned int	y;
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
	t_vector					current_position;
	struct s_position			end_position;
	struct s_position			end_ray;
	double						angle;
	mlx_image_t					*player_image;
	mlx_image_t					*map_player;
};

struct s_game
{
	mlx_t					*mlx;
	mlx_image_t				*bg_img;
	mlx_image_t				*game_screen;
	mlx_image_t				*floor;
	mlx_image_t				*ceiling;
	mlx_texture_t			*south;
	mlx_texture_t			*north;
	mlx_texture_t			*east;
	mlx_texture_t			*west;
	int						ceiling_color;
	int						floor_color;
	double					width;
	double					height;
	double					distance;
	unsigned char			color[4];
	int						n;
	struct s_map			*map_data;
	int						hit;
	struct s_player			player_data;
};

struct s_map
{
	char	**map_array;
	char	**map_copy;
	char	**map;
	int		height;
	int		width;
	char	*elements[7];
};

typedef enum DIR
{
 NORTH,
 EAST,
 SOUTH,
 WEST
} t_direction;

void		game_setup(char *argv);
void		init_map_data(t_game **game_data, t_map **map_data, char *map_file);
void		destroy_map_data(t_map *map_data);
void		print_error(int error);
void		cleanup_and_exit(int error, int file, char *buffer);
int			get_total_bytes(char *filename);
char		*read_map(char *filename);
int			has_invalid_map_extension(char *filename);
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
void		line_draw(t_vector *player, double angle, t_game *game_data);
void		line_draw2(t_vector *pointA, struct s_position *pointB, char **map, t_game *game_data);
void		draw_fov(t_game **game_data);
void		update_origin(t_game **game_data);
void		update_end(t_game **game_data, double fov_angle);
void		draw_wall(t_game **game_data, t_int_vector center, double fov);
void		draw_sin(t_game **game_data);
int			get_rgba(int r, int g, int b, int a);
void		add_bg_image(t_game **game_data);
int			get_color_texture(mlx_texture_t *tex, t_game *game_data, int y);
void		print_array(char **array);
void		player_angle(t_game **data, char orientation);
void		flood_fill(int x, int y, char **map);
void		check_borders(char **map);
void		check_map_symbols(char **map, t_game **game_data);
void		parse_map(t_game **game_data, t_map **map_data);
void		malloc_map_struct(t_map **map_data, void (*f)(void *), void *data);
void		destroy_map_data(t_map *map_data);
void		store_path(t_game **game_data, char *symbol, char *path);
void		init_map_data(t_game **game_data, t_map **map_data, char *map_file);
void		parse_color_code(char *string);
int			get_decimals(char *string);
void		register_color_in_struc(t_game **game_data, char *string);
void		parse_color(t_game **game_data, char *string);
void		parse_path(t_game **game_data, char *string);
void		parse_element(t_game **game_data, char *string);
void		print_array(char **array);
int			is_valid_element(t_map **map_data, char *map);
char		*try_read_map(char *map_file);
char		**try_split_string(char *string, t_map *map_data);
void		check_neighbors(char **map, int x, int y);

#endif
