
#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>

int			get_total_bytes(char *filename);
char		*read_map(char *file);

#endif
