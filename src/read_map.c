
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
	{
		printf("strerror: %s\n", strerror(errno));
		return (0);
	}
	buffer = (char *)malloc(sizeof(char) * 100);
	if (!buffer)
	{
		close(fd);
		return (0);
	}
	bytes = read(fd, buffer, 100);
	if (bytes == 0)
	{
		close(fd);
		free(buffer);
		return (0);
	}
	total_bytes += bytes;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, 100);
		total_bytes += bytes;
	}
	close(fd);
	free(buffer);
	return (total_bytes);
}
