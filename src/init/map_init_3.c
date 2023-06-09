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
		parse_color_code(block, string);
		register_color_in_struc(block, game_data, string);
	}
	else
	{
		free_all_memory_blocks(block);
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
		store_path(game_data, symbol, string + i);
	else
	{
		free_all_memory_blocks(block);
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

void	print_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i] != NULL)
		printf("%s\n", array[i]);
}
