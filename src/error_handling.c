
#include "../include/cub3D.h"

void	print_error(int error)
{
	write(2, "Error: ", 7);
	ft_putstr_fd(strerror(error), 2);
	write(2, "\n", 1);
}

int	handle_error(int error)
{
	if (error == EMPTY_MAP)
	{
		write(2, "Error: Empty map\n", 17);
		exit(error);
	}
	if (error == BAD_MAP_FILE)
	{
		write(2, "Error: Bad map file\n", 20);
		exit(error);
	}
	print_error(error);
	exit(error);
}

void	cleanup_and_exit(int error, int file, char *buffer)
{
	if (file > 0)
		close(file);
	if (buffer != NULL)
		free(buffer);
	print_error(error);
	exit(error);
}

int	filename_extension_is_valid(char *filename)
{
	int	filename_length;

	filename_length = ft_strlen(filename);
	if (ft_strncmp(filename + (filename_length - 4), ".cub\0", 5))
		return(FALSE);
	return(TRUE);
}

int	filename_is_valid(char *filename)
{
	if (filename_extension_is_valid(filename))
		return (TRUE);
	return (handle_error(BAD_MAP_FILE));
}
