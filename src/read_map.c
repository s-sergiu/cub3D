
#include "../include/cub3D.h"

int	get_total_bytes(char *filename)
{
	int		fd;
	char	*buffer;
	int		total_bytes;
	int		bytes;

	total_bytes = 0;
	bytes = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		printf("strerror: %s\n", strerror(errno));
	buffer = (char *)malloc(sizeof(char) * 1);
	if (!buffer)
		return (0);
	bytes = read(fd, buffer, 1);
	total_bytes += bytes;
	if (total_bytes == 0)
		return (0);
	while (bytes > 0)
	{
		bytes = read(fd, buffer, 1);
		total_bytes += bytes;
	}
	close(fd);
	free(buffer);
	return (total_bytes);
}
