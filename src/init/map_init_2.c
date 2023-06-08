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
	int	i;
	int	digit;
	int	comma;

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
			else if ((digit == 3 && ft_isdigit(string[i]))
				|| (digit == 3 && !ft_isdigit(string[i])))
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
	int	m;
	int	j;

	j = 0;
	while (string[j] != ',' && string[j] != 0)
		j++;
	m = (pow(10, j - 1));
	return (m);
}

void	register_color_in_struc(t_game **game_data, char *string)
{
	int	i;
	int	m;
	int	index;
	int	color;

	i = -1;
	m = 0;
	index = 0;
	(*game_data)->color[0] = 0;
	(*game_data)->color[1] = 0;
	(*game_data)->color[2] = 0;
	color = 0;
	while (string[++i] != 0)
	{
		if (m == 0)
			m = get_decimals(string + i);
		while (string[i] != ',' && string[i] != 0)
		{
			color += m * (string[i] - '0');
			(*game_data)->color[index] = color;
			i++;
			m = m / 10;
		}
		if (color < 0 || color > 255)
		{
			printf("Color is not in 0 to 255 range\n");
			exit(1);
		}
		m = 0;
		color = 0;
		index++;
		if (string[i] == 0)
			break ;
	}
	(*game_data)->color[3] = 0;
}
