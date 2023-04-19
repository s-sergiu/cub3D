
#include "../../../include/libarrtools/libarrtools.h"

int	get_map_height(char **map_array)
{
	int	index;

	index = 0;
	while (map_array[index])
		index++;
	return (index);
}
