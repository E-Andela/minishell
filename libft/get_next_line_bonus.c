/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/24 17:59:09 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/17 14:37:43 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_remainder(char *line_nlc_remainder)
{
	char	*remainder;
	int		nlc;
	int		i;

	i = 0;
	nlc = 0;
	if (line_nlc_remainder[i] == '\0')
		return (line_nlc_remainder);
	while (line_nlc_remainder[nlc] != '\0' && line_nlc_remainder[nlc] != '\n')
		nlc++;
	if (line_nlc_remainder[nlc] == '\n')
		nlc++;
	remainder = (char *)malloc(sizeof(char) * \
	(ft_strlen_gnl(&line_nlc_remainder[nlc]) + 1));
	if (remainder == NULL)
		return (free(line_nlc_remainder), NULL);
	while (line_nlc_remainder[nlc] != '\0')
	{
		remainder[i] = line_nlc_remainder[nlc];
		nlc++;
		i++;
	}
	free(line_nlc_remainder);
	remainder[i] = '\0';
	return (remainder);
}

char	*ft_get_line(char *line_nlc_remainder)
{
	char	*line;
	int		nlc;
	int		i;

	i = 0;
	nlc = 0;
	if (line_nlc_remainder[nlc] == '\0')
		return (NULL);
	while (line_nlc_remainder[nlc] != '\0' && line_nlc_remainder[nlc] != '\n')
		nlc++;
	line = (char *)malloc(sizeof(char) * (nlc + 2));
	if (line == NULL)
		return (NULL);
	while (line_nlc_remainder[i] != '\0' && line_nlc_remainder[i] != '\n')
	{
		line[i] = line_nlc_remainder[i];
		i++;
	}
	if (line_nlc_remainder[i] == '\n')
	{
		line[i] = line_nlc_remainder[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read(int fd, char *line_nlc_remainder)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	ft_memset_gnl(buffer, '\0', BUFFER_SIZE + 1);
	while (ft_strchr_gnl(buffer, '\n') == NULL && (bytes_read != 0))
	{
		temp = line_nlc_remainder;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(line_nlc_remainder), NULL);
		buffer[bytes_read] = '\0';
		line_nlc_remainder = ft_strjoin_gnl(temp, buffer);
		free(temp);
		if (line_nlc_remainder == NULL || !*line_nlc_remainder)
			return (free(buffer), free(line_nlc_remainder), NULL);
	}
	free(buffer);
	return (line_nlc_remainder);
}

char	*get_next_line(int fd)
{
	static char	*substrings[FD_LIMIT + 1] = {NULL};
	char		*next_line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FD_LIMIT)
		return (NULL);
	substrings[fd] = ft_read(fd, substrings[fd]);
	if (substrings[fd] == NULL)
		return (NULL);
	next_line = ft_get_line(substrings[fd]);
	if (next_line == NULL)
		return (NULL);
	substrings[fd] = ft_get_remainder(substrings[fd]);
	if (substrings[fd] == NULL)
		return (NULL);
	return (next_line);
}
