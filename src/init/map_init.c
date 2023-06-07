
#include "cub3D.h"

void	store_path(t_game **game_data, char *symbol, char *path)
{
	if (!ft_strncmp(symbol, "NO", 2))
		(*game_data)->north = mlx_load_png(path);	
	else if (!ft_strncmp(symbol, "SO", 2))
		(*game_data)->south = mlx_load_png(path);	
	else if (!ft_strncmp(symbol, "WE", 2))
		(*game_data)->west = mlx_load_png(path);	
	else if (!ft_strncmp(symbol, "EA", 2))
		(*game_data)->east = mlx_load_png(path);	
}

void	parse_color_code(char *string)
{
	int i;
	int digit;
	int comma;

	digit = 0;
	comma = 0;
	i = 0;
	while (comma < 3)
	{
		while (digit < 3)
		{
			if (ft_isdigit(string[i++]))
				digit++;
			else
				exit(1);
			if (string[i] == ',' || string[i] == '\0')
				break ;
			else if ((digit == 3 && ft_isdigit(string[i])) || (digit == 3 && !ft_isdigit(string[i])))
				exit(1);
		}
		i++;
		comma++;
		digit = 0;
	}
	if (string[i - 1] != '\0')
		exit(1);
}

int	get_decimals(char *string)
{
	int m;
	int j;

	j = 0;
	while(string[j] != ',' && string[j] != 0)
	{
		j++;
	}
	m = (pow(10, j - 1));

	return(m);
}

void	register_color_in_struc(t_game **game_data, char *string)
{
	int i;
	int m;
	int index;

	i = -1;
	m = 0;
	index = 0;
	(*game_data)->color[0] = 0;
	(*game_data)->color[1] = 0;
	(*game_data)->color[2] = 0;
	while (string[++i] != 0)
	{
		if (m == 0)
			m = get_decimals(string + i);
		while (string[i] != ',' && string[i] != 0)
		{
			(*game_data)->color[index] += m * (string[i] - '0');
			i++;
			m = m / 10;
		}
		m = 0;
		index++;
		if (string[i] == 0)
			break;
	}
	(*game_data)->color[3] = 0;
}

void	parse_color(t_game **game_data, char *string)
{
	char	*symbol;
	int		i;

	symbol = string;
	string = string + 2;
	i = 0;
	while (string[i] == 32 || string[i] == 9)
		i++;
	if ((symbol + 1)[0] == 9 || (symbol + 1)[0] == 32)
	{
		parse_color_code(string);
		register_color_in_struc(game_data, string);
	}
	else 
		exit(1);
}

void	parse_path(t_game **game_data, char *string)
{
	char	*symbol;
	int		i;
	int		fd;

	symbol = string;
	string = string + 2;
	i = 0;
	while (string[i] == 32 || string[i] == 9)
		i++;
	fd = open(string + i, O_RDONLY);
	if (fd != -1 && ((symbol + 2)[0] == 9 || (symbol + 2)[0] == 32))
		store_path(game_data, symbol, string + i);

	else 
		exit(1);
}

void	parse_element(t_game **game_data, char *string)
{
	if (!ft_strncmp(string, "NO", 2))
		parse_path(game_data, string);
	else if (!ft_strncmp(string, "SO", 2))
		parse_path(game_data, string);
	else if (!ft_strncmp(string, "WE", 2))
		parse_path(game_data, string);
	else if (!ft_strncmp(string, "EA", 2))
		parse_path(game_data, string);
	else if (!ft_strncmp(string, "F", 1))
	{
		parse_color(game_data, string);
		(*game_data)->floor_color= get_rgba((*game_data)->color[0], 
			(*game_data)->color[1], (*game_data)->color[2], 255); 
	}
	else if (!ft_strncmp(string, "C", 1))
	{
		parse_color(game_data, string);
		(*game_data)->ceiling_color = get_rgba((*game_data)->color[0], 
			(*game_data)->color[1], (*game_data)->color[2], 255); 
	}
}

void	print_array(char **array)
{
	int i;

	i = -1;
	while (array[++i] != NULL)
		printf("%s\n", array[i]);
}

int	is_valid_element(t_map **map_data, char *map)
{
	int i = -1;
	int j = -1;

	while ((*map_data)->elements[++j])
	{
		i = -1;
		while (map[++i])
		{
			while (map[i] == 32 || map[i] == 9)
				i++;
			if (!ft_strncmp(map + i, (*map_data)->elements[j], 
				ft_strlen((*map_data)->elements[j])))
			{
				(*map_data)->elements[j] = "0";
				return (i);
			}
			else
				break;
		}
	}
	printf("earror\n");
	return (-1);
}

char	*try_read_map(char *map_file)
{
	char	*pointer;

	pointer = read_map(map_file);
	if (pointer == NULL)
		exit(errno);
	return (pointer);
}

char	**try_split_string(char *string, t_map *map_data)
{
	char	**map_array;

	map_array = ft_split(string, '\n');
	if (map_array == NULL)
	{
		free(map_data);
		exit(errno);
	}
	return (map_array);
}

void	check_neighbors(char **map, int x, int y)
{
	if (map[x + 1] == NULL || map[x + 1][y] == 32)
		exit(1);
	if (map[x - 1] == NULL || map[x - 1][y] == 32)
		exit(1);
	if (!map[x][y + 1] || map[x][y + 1] == 32)
		exit(1);
	if (!map[x][y - 1] || map[x][y - 1] == 32)
		exit(1);
}

void	flood_fill(int x, int y, char **map)
{
	char wall;

	if (x > 13 || x < 0)
		return ;
	wall = map[x][y];
	if (wall == 0 || wall == 32 || wall == 'x' || wall == '1')
		return ;
	else
	{
		map[x][y] = 'x';
		check_neighbors(map, x , y);
		flood_fill(x - 1, y, map);
		flood_fill(x, y -1, map);
		flood_fill(x, y + 1, map);
		flood_fill(x + 1, y, map);
	}
}

void	check_borders(char **map)
{
	int i;

	i = 0;
	while(map[1][i++] != '0')
		i++;
	flood_fill(1, i, map);	
}

void	check_map_symbols(char **map, t_game **game_data)
{
	int i;
	int j;
	int player;
	char symbol;

	i = -1;
	j = -1;
	player = 0;
	while (map[++i])
	{
		while(map[i][++j])
		{
			while (map[i][j] == 32)
				j++;
			symbol = map[i][j];
			if (symbol != '0' && symbol != '1' && symbol != 'N' && symbol != 'S' 
				&& symbol != 'E' && symbol != 'W')
				exit(1);
			else if (symbol == 'E' || symbol == 'W' || symbol == 'N' || symbol == 'S')
			{
				player_angle(game_data, symbol);
				player++;
			}
		}
		j = -1;
	}
	if (player > 1)
		exit(1);
}

void	parse_map(t_game **game_data, t_map **map_data)
{
	int i;
	char **map;
	int	sequence;
	int	index;

	i = -1;
	map = (*map_data)->map_array;
	sequence = 0;
	while (map[++i])	
	{
		if (ft_strlen(map[i]))
		{
			if (sequence < 6)
			{
				index = is_valid_element(map_data, map[i]);
				if (index >= 0)
				{
					parse_element(game_data, (map[i]) + index);
					sequence++;
				}
				else
					exit(1);
			}
			else
			{
				(*map_data)->map = map + sequence;
				(*map_data)->map_copy = (*map_data)->map_copy + sequence;
				(*map_data)->width =ft_strlen(map[0]) * TILE;
				(*map_data)->height = arrtools_arrlen(map) * TILE;
				check_borders((*map_data)->map_copy);
				check_map_symbols((*map_data)->map, game_data);
				break;
			}
		}
	}
}

void	malloc_map_struct(t_map **map_data, void (*f)(void *), void *data)
{
	*map_data = (t_map *)malloc(sizeof(t_map));
	if (map_data == NULL)
	{
		f(data);
		exit(errno);
	}
}

void	destroy_map_data(t_map *map_data)
{
	if (map_data->map_array)
		arrtools_free(map_data->map_array);
	free(map_data);
}

void	init_map_data(t_game **game_data, t_map **map_data, char *map_file)
{
	char	*map_string;

	map_string = try_read_map(map_file);
	malloc_map_struct(map_data, free, map_string);
	(*map_data)->elements[0] = "NO";
	(*map_data)->elements[1] = "SO";
	(*map_data)->elements[2] = "EA";
	(*map_data)->elements[3] = "WE";
	(*map_data)->elements[4] = "C";
	(*map_data)->elements[5] = "F";
	(*map_data)->elements[6] = NULL;
	(*map_data)->map_array = try_split_string(map_string, *map_data);
	(*map_data)->map_copy = try_split_string(map_string, *map_data);
	(*map_data)->width = ft_strlen((*map_data)->map_array[0]) * TILE;
	(*map_data)->height = arrtools_arrlen((*map_data)->map_array) * TILE;
	parse_map(game_data, map_data);
}
