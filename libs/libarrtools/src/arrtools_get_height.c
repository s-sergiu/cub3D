
#include "libarrtools.h"

int	arrtools_arrlen(char **map_array)
{
	int	index;

	if (!map_array)
		return (0);
	index = 0;
	while (map_array[index])
		index++;
	return (index);
}
