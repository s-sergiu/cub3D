#include "cub3D.h"

void	parse_color(t_memory **block, t_game **game_data, char *string)
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
		parse_color_code(block, string + i);
		register_color_in_struc(block, game_data, string + i);
	}
	else
	{
		free_all_memory_blocks(block);
		printf("Error\n");
		printf("Invalid color element structure!\n");
		exit(1);
	}
}

void	parse_path(t_memory **block, t_game **game_data, char *string)
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
		store_path(block, game_data, symbol, string + i);
	else
	{
		free_all_memory_blocks(block);
		printf("Error\n");
		printf("Invalid path element structure!\n");
		exit(1);
	}
	close(fd);
}

void	parse_element(t_memory **block, t_game **game_data, char *string)
{
	if (!ft_strncmp(string, "NO", 2))
		parse_path(block, game_data, string);
	else if (!ft_strncmp(string, "SO", 2))
		parse_path(block, game_data, string);
	else if (!ft_strncmp(string, "WE", 2))
		parse_path(block, game_data, string);
	else if (!ft_strncmp(string, "EA", 2))
		parse_path(block, game_data, string);
	else if (!ft_strncmp(string, "F", 1))
	{
		parse_color(block, game_data, string);
		(*game_data)->floor_color = get_rgba((*game_data)->color[0],
				(*game_data)->color[1], (*game_data)->color[2], 255);
	}
	else if (!ft_strncmp(string, "C", 1))
	{
		parse_color(block, game_data, string);
		(*game_data)->ceiling_color = get_rgba((*game_data)->color[0],
				(*game_data)->color[1], (*game_data)->color[2], 255);
	}
}

void	store_path(t_memory **block, t_game **game_data,
			char *symbol, char *path)
{
	if (!ft_strncmp(symbol, "NO", 2))
	{
		(*game_data)->north = mlx_load_png(path);
		add_memory_block(block, (*game_data)->north, 69);
	}
	else if (!ft_strncmp(symbol, "SO", 2))
	{
		(*game_data)->south = mlx_load_png(path);
		add_memory_block(block, (*game_data)->south, 69);
	}
	else if (!ft_strncmp(symbol, "WE", 2))
	{
		(*game_data)->west = mlx_load_png(path);
		add_memory_block(block, (*game_data)->west, 69);
	}
	else if (!ft_strncmp(symbol, "EA", 2))
	{
		(*game_data)->east = mlx_load_png(path);
		add_memory_block(block, (*game_data)->east, 69);
	}
}

void	flood_fill(t_memory **block, int x, int y, char **map)
{
	char	wall;
	int		height;

	height = arrtools_arrlen(map);
	if (x == height || x < 0)
		return ;
	wall = map[x][y];
	if (wall == 0 || wall == 32 || wall == 'x' || wall == '1')
		return ;
	else
	{
		map[x][y] = 'x';
		check_neighbors(block, map, x, y);
		flood_fill(block, x - 1, y, map);
		flood_fill(block, x, y -1, map);
		flood_fill(block, x, y + 1, map);
		flood_fill(block, x + 1, y, map);
	}
}
