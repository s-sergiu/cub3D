
#include "../include/cub3D.h"

int	return_close_and_free(int return_value, int fd, char *buffer)
{
	close(fd);
	if (buffer != NULL)
		free(buffer);
	return (return_value);
}

int	print_error(int error_number)
{
	printf("Error: %s\n", strerror(error_number));
	return (0);
}

int	get_total_bytes(char *filename)
{
	int		fd;
	char	*buffer;
	int		total_bytes;
	int		bytes;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_error(errno));
	buffer = (char *)malloc(sizeof(char) * 100);
	if (!buffer)
		return (return_close_and_free(0, fd, NULL));
	bytes = read(fd, buffer, 100);
	if (bytes == 0)
		return_close_and_free(0, fd, NULL);
	total_bytes = bytes;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, 100);
		total_bytes += bytes;
	}
	return (return_close_and_free(total_bytes, fd, buffer));
}

char	*read_map(char *file)
{
	int fd;
	int bytes;
	char *buffer;

	bytes = get_total_bytes(file);
	printf("bytes: %d\n", bytes);
	if (bytes == 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * bytes + 1);
	if (!buffer)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free(buffer);
		return (NULL);
	}
	if (read(fd, buffer, bytes) == -1)
	{
		close(fd);
		free(buffer);
		return(NULL);
	}
	buffer[bytes] = 0;
	close(fd);
	return (buffer);
}
