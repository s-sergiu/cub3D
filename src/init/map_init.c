
#include "cub3D.h"

void	print_array(char **array)
{
	int i;

	i = -1;
	while (array[++i] != NULL)
		printf("%s\n", array[i]);
}

int	is_valid_element(char *map)
{
	char *elements[7] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	int i = -1;
	int j = -1;
	while (elements[++j])
	{
		i = -1;
		while (map[++i])
		{
			while (map[i] == 32 || map[i] == 9)
				i++;
			if (!ft_strncmp(map + i, elements[j], ft_strlen(elements[j])))
			{
				return (1);
			}
			else
				break;
		}
	}
	printf("earror\n");
	return (0);
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
		free(string);
		free(map_data);
		exit(errno);
	}
	free(string);
	return (map_array);
}

void	parse_map(t_map **map_data)
{
	int i;
	char **map;
	int	sequence;

	i = -1;
	map = (*map_data)->map_array;
	sequence = 0;
	while (map[++i])	
	{
		if (ft_strlen(map[i]))
		{
			if (sequence < 6)
			{
				//parse the things above the map
				if (is_valid_element(map[i]))
				{
					printf("yes! element %s\n", map[i]);
					sequence++;
				}
				else
				{
					printf("eror else: ");
					printf("sequence %d\n", sequence);
					exit(1);
				}
			}
			else
			{
				//parse the map
				//start storing map in struct	
				(*map_data)->map = map + sequence;
				(*map_data)->width =ft_strlen(map[0]) * TILE;
				(*map_data)->height = arrtools_arrlen(map) * TILE;
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

void	init_map_data(t_map **map_data, char *map_file)
{
	char	*map_string;

	map_string = try_read_map(map_file);
	malloc_map_struct(map_data, free, map_string);
	(*map_data)->map_array = try_split_string(map_string, *map_data);
	(*map_data)->width = ft_strlen((*map_data)->map_array[0]) * TILE;
	(*map_data)->height = arrtools_arrlen((*map_data)->map_array) * TILE;
	parse_map(map_data);
}
