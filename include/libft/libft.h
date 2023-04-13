#ifndef LIBFT_H
# define LIBFT_H

# include "../cub3D.h"

char				**ft_split(char const *s, char c);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				ft_putstr_fd(char *s, int fd);

#endif
