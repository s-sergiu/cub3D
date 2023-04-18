
#include <cub3D.h>

void	print_error(int error)
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
	write(2, "Error: ", 7);
	ft_putstr_fd(strerror(error), 2);
	write(2, "\n", 1);
	exit(error);
}

void	cleanup_and_exit(int error, int file, char *buffer)
{
	if (file > 0)
		close(file);
	if (buffer != NULL)
		free(buffer);
	print_error(error);
}

int	has_invalid_map_extension(char *filename)
{
	int	filename_length;

	filename_length = ft_strlen(filename);
	if (ft_strncmp(filename + (filename_length - 4), ".cub\0", 5))
		return(TRUE);
	return(FALSE);
}

int	is_directory(char *filename)
{
	int	file;

	file = open(filename, O_DIRECTORY);
	if (file == -1)
		return (FALSE);
	close(file);
	return (TRUE);
}

int	is_valid_filename(char *filename)
{
	if (is_directory(filename))
		print_error(IS_DIRECTORY);
	if (has_invalid_map_extension(filename))
		print_error(BAD_MAP_FILE);
	return (TRUE);
}
