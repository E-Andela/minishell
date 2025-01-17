/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/23 14:29:03 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/17 14:37:54 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	size_t			i;
	unsigned char	ch;

	if (s == NULL)
		return (NULL);
	ch = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
			return ((char *)s + i);
		i++;
	}
	if (!ch && s[i] == '\0')
		return ((char *)s + i);
	return (NULL);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	strlen1;
	size_t	strlen2;
	size_t	i;
	size_t	j;
	char	*str;

	strlen1 = ft_strlen(s1);
	strlen2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (strlen1 + strlen2 + 1));
	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	while (i < strlen1)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < strlen2)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

void	*ft_memset_gnl(void *s, int c, size_t n)
{
	char	*str;

	str = (char *)s;
	while (n != 0)
	{
		str[n - 1] = c;
		n--;
	}
	return (s);
}
