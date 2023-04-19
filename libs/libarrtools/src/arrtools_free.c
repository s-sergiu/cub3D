
#include "libarrtools.h"

void	arrtools_free(char **string_array)
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
