
#include "../../include/map_utils/map_utils.h"

void	print_error(int error_number)
{
	write(2, "Error: ", 7);
	ft_putstr_fd(strerror(error_number), 2);
	write(2, "\n", 1);
}

int	handle_error(int error_number)
{
	if (error_number == EMPTY_MAP)
	{
		write(2, "Error: Empty map\n", 17);
		exit(error_number);
	}
	if (error_number == BAD_MAP_FILE)
	{
		write(2, "Error: Bad map file\n", 20);
		exit(error_number);
	}
	print_error(error_number);
	exit(error_number);
}

void	cleanup_and_exit(int error_number, int fd, char *buffer)
{
	if (fd > 0)
		close(fd);
	if (buffer != NULL)
		free(buffer);
	print_error(error_number);
	exit(error_number);
}

/*
	get_total_bytes:
	This function returns the total number of bytes in a file.
*/

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

/*
	read_map:
	This function reads a file and returns its 
	contents in a string.
*/

char	*read_map(char *file)
{
	int fd;
	int bytes;
	char *buffer;

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

/*
	filename_is_valid:
	Checks if the filename is ending with extension '.cub'.
*/

int	filename_is_valid(char *filename)
{
	int	filename_length;

	filename_length = ft_strlen(filename);
	if (ft_strncmp(filename + (filename_length - 4), ".cub\0", 5))
		handle_error(BAD_MAP_FILE);
	return (TRUE);
}
