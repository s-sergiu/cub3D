#include "cub3D.h"

void	invalid_element_symbol(t_memory **block)
{
	free_all_memory_blocks(block);
	printf("Error\n");
	printf("Invalid element symbol!\n");
	exit(1);
}

void	map_check(t_memory **block, t_game **game_data, int sequence,
		t_map **map_data)
{
	char	**map;

	map = (*map_data)->map_array;
	(*map_data)->map = map + sequence;
	(*map_data)->map_copy = (*map_data)->map_copy + sequence;
	(*map_data)->width = ft_strlen(map[0]) * TILE;
	(*map_data)->height = arrtools_arrlen(map) * TILE;
	check_map_symbols(block, map_data, game_data);
	check_borders(block, (*map_data)->map_copy);
}

void	parse_map(t_memory **block, t_game **game_data, t_map **map_data)
{
	int		i;
	int		sequence;
	int		index;

	i = -1;
	sequence = -1;
	while ((*map_data)->map_array[++i])
	{
		if (ft_strlen((*map_data)->map_array[i]))
		{
			if (++sequence < 6)
			{
				index = is_valid_element(map_data, (*map_data)->map_array[i]);
				if (index < 0)
					invalid_element_symbol(block);
				parse_element(block, game_data, ((*map_data)->map_array[i])
					+ index);
			}
			else
			{
				map_check(block, game_data, sequence, map_data);
				break ;
			}
		}
	}
}

void	malloc_map_struct(t_memory **block, t_map **map_data)
{
	(*map_data) = malloc_to_block(block, sizeof(t_map));
	if ((*map_data) == NULL)
	{
		printf("Error\n");
		printf("Failed initializing map struct!\n");
		free_all_memory_blocks(block);
		exit(errno);
	}
}

void	init_map_data(t_memory **block, t_game **game_data,
				t_map **map_data, char *map_file)
{
	char	*map_string;

	map_string = try_read_map(block, map_file);
	add_memory_block(block, map_string, sizeof(char *));
	malloc_map_struct(block, map_data);
	(*map_data)->elements[0] = "NO";
	(*map_data)->elements[1] = "SO";
	(*map_data)->elements[2] = "EA";
	(*map_data)->elements[3] = "WE";
	(*map_data)->elements[4] = "C";
	(*map_data)->elements[5] = "F";
	(*map_data)->elements[6] = NULL;
	(*map_data)->map_array = try_split_string(block, map_string);
	(*map_data)->map_copy = try_split_string(block, map_string);
	(*map_data)->width = ft_strlen((*map_data)->map_array[0]) * TILE;
	(*map_data)->height = arrtools_arrlen((*map_data)->map_array) * TILE;
	parse_map(block, game_data, map_data);
}
