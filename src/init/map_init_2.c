#include "cub3D.h"

void	color_code_error(t_memory **block)
{
	printf("Error\n");
	printf("Invalid color code!\n");
	free_all_memory_blocks(block);
	exit(1);
}

void	parse_color_code(t_memory **block, char *string)
{
	int	i;
	int	digit;
	int	comma;

	digit = -1;
	comma = -1;
	i = 0;
	while (++comma < 3)
	{
		while (++digit < 3)
		{
			if (!ft_isdigit(string[i++]))
				color_code_error(block);
			if (string[i] == ',' || string[i] == '\0')
				break ;
			else if ((digit == 3 && ft_isdigit(string[i]))
				|| (digit == 3 && !ft_isdigit(string[i])))
				color_code_error(block);
		}
		i++;
		digit = -1;
	}
	if (string[i - 1] != '\0')
		color_code_error(block);
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

void	color_not_in_range(t_memory **block)
{
	free_all_memory_blocks(block);
	printf("Color is not in 0 to 255 range\n");
	exit(1);
}

void	register_color_in_struc(t_memory **block, t_game **game_data,
				char *string)
{
	int	i;
	int	m;
	int	index;
	int	color;

	i = -1;
	index = 0;
	while (string[++i] != 0)
	{
		m = 0;
		color = 0;
		if (m == 0)
			m = get_decimals(string + i);
		while (string[i] != ',' && string[i] != 0)
		{
			color += m * (string[i++] - '0');
			(*game_data)->color[index] = color;
			m = m / 10;
		}
		if (color < 0 || color > 255)
			color_not_in_range(block);
		index++;
		if (string[i] == 0)
			break ;
	}
}
