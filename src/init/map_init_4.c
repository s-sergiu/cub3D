#include "cub3D.h"

int	is_valid_element(t_map **map_data, char *map)
{
	int	i;
	int	j;

	j = -1;
	i = -1;
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
				break ;
		}
	}
	return (-1);
}

char	*try_read_map(t_memory **block, char *map_file)
{
	char	*pointer;

	pointer = read_map(map_file);
	if (pointer == NULL)
	{
		free_all_memory_blocks(block);
		printf("Error\n");
		printf("Failed reading map file!\n");
		exit(errno);
	}
	return (pointer);
}

char	**try_split_string(t_memory **block, char *string)
{
	char	**map_array;

	map_array = ft_split(block, string, '\n');
	if (map_array == NULL)
	{
		free_all_memory_blocks(block);
		printf("Error\n");
		printf("Failed creating 2d map array!\n");
		exit(errno);
	}
	return (map_array);
}

void	error_and_exit(t_memory **block)
{
	printf("Error\n");
	printf("Map is leaking\n");
	free_all_memory_blocks(block);
	exit(1);
}

void	check_neighbors(t_memory **block, char **map, int x, int y)
{
	if ((int)ft_strlen(map[x + 1]) < y)
		error_and_exit(block);
	if (map[x + 1] == NULL || map[x + 1][y] == 32 || map[x + 1][y] == 0)
		error_and_exit(block);
	if (map[x - 1] == NULL || map[x - 1][y] == 32 || map[x - 1][y] == 0)
		error_and_exit(block);
	if (!map[x][y + 1] || map[x][y + 1] == 32 || map[x][y + 1] == 0)
		error_and_exit(block);
	if (!map[x][y - 1] || map[x][y - 1] == 32 || map[x][y + 1] == 0)
		error_and_exit(block);
}
