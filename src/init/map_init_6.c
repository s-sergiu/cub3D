#include "cub3D.h"

void	check_borders(t_memory **block, char **map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map[++i])
	{
		while (map[i][++j])
		{
			if (map[i][j] == '0')
				flood_fill(block, i, j, map);
		}
		j = -1;
	}
}

void	illegal_map_symbol(t_memory **block)
{
	free_all_memory_blocks(block);
	printf("Error\n");
	printf("Illegal map symbol!\n");
	exit(1);
}

void	player_number_eror(t_memory **block)
{
	free_all_memory_blocks(block);
	printf("No player or more than 1 players in the map\n");
	exit(1);
}

void	check_row_symbols(t_memory **block, t_map **map_data,
			int i, t_game **game_data)
{
	int		j;
	char	*map;

	j = -1;
	map = (*map_data)->map[i];
	while (map[++j])
	{
		while (map[j] == 32)
		{
			if (map[j - 1] == '1' || map [j - 1] == '0')
				change_empty_space(map_data, i, j);
			j++;
		}
		if (map[j] != '0' && map[j] != '1' && map[j] != 'N' && map[j]
			!= 'S' && map[j] != 'E' && map[j] != 'W')
			illegal_map_symbol(block);
		else if (map[j] == 'E' || map[j] == 'W'
			|| map[j] == 'N' || map[j] == 'S')
		{
			player_angle(game_data, map[j]);
			(*game_data)->player_count++;
		}
	}
}

void	check_map_symbols(t_memory **block, t_map **map_data,
					t_game **game_data)
{
	int		i;
	char	**map;

	i = -1;
	map = (*map_data)->map;
	while (map[++i])
		check_row_symbols(block, map_data, i, game_data);
	if ((*game_data)->player_count != 1)
		player_number_eror(block);
}
