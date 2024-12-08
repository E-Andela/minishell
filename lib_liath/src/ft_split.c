/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 13:29:13 by livliege      #+#    #+#                 */
/*   Updated: 2024/09/17 17:14:23 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
Function name       ft_split
Prototype           char **ft_split(char const *s, char c);
Turn in files       -
Parameters          s: The string to be split.
                    c: The delimiter character.
Return value        The array of new strings resulting from the split.
                    NULL if the allocation fails.
External functs.    malloc, free
Description         Allocates (with malloc(3)) and returns an array
                    of strings obtained by splitting ’s’ using the
                    character ’c’ as a delimiter. The array must end
                    with a NULL pointer.
*/

#include "../lib_liath.h"

void	*ft_free(char **split_2d_array)
{
	size_t	i;

	i = 0;
	while (split_2d_array[i] != NULL)
	{
		free(split_2d_array[i]);
		i++;
	}
	free(split_2d_array);
	return (NULL);
}

size_t	ft_wordcount(char const *s, char c)
{
	int	words;
	int	new_word;
	int	i;

	words = 0;
	new_word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && new_word == 0)
		{
			new_word = 1;
			words++;
		}
		else if (s[i] == c)
			new_word = 0;
		i++;
	}
	return (words);
}

char	**ft_split_size(char const *s, char c)
{
	char	**split_2d_array;

	if (s == NULL)
		return (NULL);
	split_2d_array = (char **)malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (split_2d_array == NULL)
		return (NULL);
	split_2d_array[ft_wordcount(s, c)] = NULL;
	return (split_2d_array);
}

char	**ft_split(char const *s, char c)
{
	size_t			j;
	size_t			i;
	int				new_word;
	char			**split_2d_array;
	const size_t	size = ft_strlen(s);

	i = SIZE_MAX;
	j = 0;
	new_word = -1;
	split_2d_array = ft_split_size(s, c);
	if (split_2d_array == NULL)
		return (NULL);
	while (++i <= size)
	{
		if (s[i] != c && new_word < 0)
			new_word = i;
		else if ((s[i] == c || i == size) && new_word >= 0)
		{
			split_2d_array[j] = ft_substr(s, new_word, (i - new_word));
			new_word = -1;
			if (!split_2d_array[j++])
				return (ft_free(split_2d_array));
		}
	}
	return (split_2d_array);
}
