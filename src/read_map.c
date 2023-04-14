
#include "../include/cub3D.h"

int	get_total_bytes(char *filename)
{
	int		fd;
	char	*buffer;
	int		total_bytes;
	int		bytes;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_error(errno);
	buffer = (char *)malloc(sizeof(char) * 100);
	if (!buffer)
		cleanup_and_exit(errno, fd, NULL);
	bytes = read(fd, buffer, 100);
	if (bytes == -1)
		cleanup_and_exit(errno, fd, buffer);
	total_bytes = bytes;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, 100);
		if (bytes == -1)
			cleanup_and_exit(errno, fd, buffer);
		total_bytes += bytes;
	}
	close(fd);
	free(buffer);
	return (total_bytes);
}

char	*read_map(char *file)
{
	int		fd;
	int		bytes;
	char	*buffer;

	bytes = get_total_bytes(file);
	if (!bytes)
		handle_error(EMPTY_MAP);
	buffer = (char *)malloc(sizeof(char) * bytes + 1);
	if (!buffer)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		cleanup_and_exit(errno, 0, buffer);
	if (read(fd, buffer, bytes) == -1)
		cleanup_and_exit(errno, fd, buffer);
	buffer[bytes] = '\0';
	close(fd);
	return (buffer);
}
