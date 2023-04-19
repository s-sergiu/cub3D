#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

/**
 * @brief Splits a string into an array of strings based on a given delimiter.
 *
 * @param s The string to be split into an array of strings.
 * @param c The delimiter used to separate the words in the string.
 * @return char** A pointer to the array of strings.
 */
char				**ft_split(char const *s, char c);

/**
 * @brief Copy a string to a destination buffer with a specified maximum size.
 *
 * @param dst The destination buffer.
 * @param src The source string.
 * @param dstsize The maximum number of bytes that can be written to dst.
 *
 * @return The length of src.
 */
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);

/**
 * @brief Calculates the length of a string.
 *
 * @param str The string to calculate the length of.
 *
 * @return The length of the string.
 */
size_t				ft_strlen(const char *str);

/**
 * @brief Compare the first n bytes of two strings
 *
 * @param s1 The first string to compare
 * @param s2 The second string to compare
 * @param n The maximum number of bytes to compare
 *
 * @return An integer greater than, equal to, or less than 0, according as the
 * string s1 is greater than, equal to, or less than the string s2
 */
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * Outputs a string to a file descriptor.
 *
 * @param s The string to output.
 * @param fd The file descriptor to write to.
 */
void				ft_putstr_fd(char *s, int fd);

#endif
