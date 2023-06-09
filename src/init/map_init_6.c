#include "cub3D.h"

void	check_borders(t_memory **block, char **map)
{
	int	i;

	i = 0;
	while (map[1][i++] != '0')
		i++;
	flood_fill(block, 1, i, map);
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

void	check_row_symbols(t_memory **block, t_game **game_data, char *map)
{
	int	j;

	j = -1;
	while (map[++j])
	{
		while (map[j] == 32)
			j++;
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

void	check_map_symbols(t_memory **block, char **map, t_game **game_data)
{
	int		i;

	i = -1;
	while (map[++i])
		check_row_symbols(block, game_data, map[i]);
	if ((*game_data)->player_count != 1)
		player_number_eror(block);
}
