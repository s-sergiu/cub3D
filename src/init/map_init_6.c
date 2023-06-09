#include "cub3D.h"

void	flood_fill(int x, int y, char **map)
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
		check_neighbors(map, x, y);
		flood_fill(x - 1, y, map);
		flood_fill(x, y -1, map);
		flood_fill(x, y + 1, map);
		flood_fill(x + 1, y, map);
	}
}

void	check_borders(char **map)
{
	int	i;

	i = 0;
	while (map[1][i++] != '0')
		i++;
	flood_fill(1, i, map);
}

void	check_map_symbols(t_memory **block, char **map, t_game **game_data)
{
	int		i;
	int		j;
	int		player;
	char	symbol;

	i = -1;
	j = -1;
	player = 0;
	while (map[++i])
	{
		while (map[i][++j])
		{
			while (map[i][j] == 32)
				j++;
			symbol = map[i][j];
			if (symbol != '0' && symbol != '1'
				&& symbol != 'N' && symbol != 'S'
				&& symbol != 'E' && symbol != 'W')
			{
				free_all_memory_blocks(block);
				exit(1);
			}
			else if (symbol == 'E' || symbol == 'W'
				|| symbol == 'N' || symbol == 'S')
			{
				player_angle(game_data, symbol);
				player++;
			}
		}
		j = -1;
	}
	if (player != 1)
	{
		free_all_memory_blocks(block);
		printf("No player or more than 1 players in the map\n");
		exit(1);
	}
}
