/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lib_liath.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 20:21:00 by livliege      #+#    #+#                 */
/*   Updated: 2024/11/08 13:24:35 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_LIATH_H
# define LIB_LIATH_H


# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stddef.h>

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int	ft_isalnum(int c);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
