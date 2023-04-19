
#include "cub3D.h"

int	get_total_bytes(char *filename)
{
	int		file;
	char	*string_buffer;
	int		total_bytes;
	int		bytes_read;

	file = open(filename, O_RDONLY);
	if (file == -1)
		print_error(errno);
	string_buffer = (char *)malloc(sizeof(char) * 100);
	if (!string_buffer)
		cleanup_and_exit(errno, file, NULL);
	bytes_read = read(file, string_buffer, 100);
	if (bytes_read == -1)
		cleanup_and_exit(errno, file, string_buffer);
	total_bytes = bytes_read;
	while (bytes_read > 0)
	{
		bytes_read = read(file, string_buffer, 100);
		if (bytes_read == -1)
			cleanup_and_exit(errno, file, string_buffer);
		total_bytes += bytes_read;
	}
	close(file);
	free(string_buffer);
	return (total_bytes);
}

char	*read_map(char *filename)
{
	int		file;
	int		bytes_read;
	char	*map_string;

	bytes_read = get_total_bytes(filename);
	if (!bytes_read)
		print_error(EMPTY_MAP);
	map_string = (char *)malloc(sizeof(char) * bytes_read + 1);
	if (!map_string)
		return (NULL);
	file = open(filename, O_RDONLY);
	if (file == -1)
		cleanup_and_exit(errno, 0, map_string);
	if (read(file, map_string, bytes_read) == -1)
		cleanup_and_exit(errno, file, map_string);
	map_string[bytes_read] = '\0';
	close(file);
	return (map_string);
}
