
#include "libarrtools.h"

void	free_array_of_memory(char **string_array)
{
	int	index;	

	index = -1;
	if (string_array)
	{
		while (string_array[++index])
			free(string_array[index]);
		free(string_array);
	}	
}
