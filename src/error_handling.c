
#include "../include/cub3D.h"

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

int	filename_is_valid(char *filename)
{
	int	filename_length;

	filename_length = ft_strlen(filename);
	if (ft_strncmp(filename + (filename_length - 4), ".cub\0", 5))
		handle_error(BAD_MAP_FILE);
	return (TRUE);
}
