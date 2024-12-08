/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <marvin@42.fr>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 12:28:15 by eandela       #+#    #+#                 */
/*   Updated: 2024/09/21 21:16:15 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_token_count(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else if (s[i] == c)
			i++;
	}
	return (count);
}

static int	ft_token_size(char const *s, char c, int start)
{
	int	size;

	size = 0;
	while (s[start] && s[start] != c)
	{
		start++;
		size++;
	}
	return (size);
}

void	ft_free_dbl(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	**ft_free_double(char **ptr, int j)
{
	while (j >= 0)
	{
		free(ptr[j]);
		j--;
	}
	free(ptr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**splt;
	int		i;
	int		j;

	i = 0;
	j = 0;
	splt = (char **)malloc((ft_token_count(s, c) + 1) * sizeof(char *));
	if (!splt)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			splt[j] = ft_substr(s, i, ft_token_size(s, c, i));
			if (splt[j] == NULL)
				return (ft_free_double(splt, j - 1));
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
		else if (s[i] == c)
			i++;
	}
	splt[j] = 0;
	return (splt);
}
