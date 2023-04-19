
#include "libarrtools.h"

int	get_map_height(char **map_array)
{
	int	index;

	if (!map_array)
		return (0);
	index = 0;
	while (map_array[index])
		index++;
	return (index);
}
