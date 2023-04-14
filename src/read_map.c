
#include "../include/cub3D.h"

int	get_total_bytes(char *filename)
{
	int		file;
	char	*buffer;
	int		total_bytes;
	int		bytes_read;

	file = open(filename, O_RDONLY);
	if (file == -1)
		handle_error(errno);
	buffer = (char *)malloc(sizeof(char) * 100);
	if (!buffer)
		cleanup_and_exit(errno, file, NULL);
	bytes_read = read(file, buffer, 100);
	if (bytes_read == -1)
		cleanup_and_exit(errno, file, buffer);
	total_bytes = bytes_read;
	while (bytes_read > 0)
	{
		bytes_read = read(file, buffer, 100);
		if (bytes_read == -1)
			cleanup_and_exit(errno, file, buffer);
		total_bytes += bytes_read;
	}
	close(file);
	free(buffer);
	return (total_bytes);
}

char	*read_map(char *filename)
{
	int		file;
	int		bytes_read;
	char	*map;

	bytes_read = get_total_bytes(filename);
	if (!bytes_read)
		handle_error(EMPTY_MAP);
	map = (char *)malloc(sizeof(char) * bytes_read + 1);
	if (!map)
		return (NULL);
	file = open(filename, O_RDONLY);
	if (file == -1)
		cleanup_and_exit(errno, 0, map);
	if (read(file, map, bytes_read) == -1)
		cleanup_and_exit(errno, file, map);
	map[bytes_read] = '\0';
	close(file);
	return (map);
}
