/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 19:09:55 by livliege      #+#    #+#                 */
/*   Updated: 2024/09/17 17:14:33 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
Function name       ft_substr
Prototype           char *ft_substr(char const *s, unsigned int start, 
						size_t len);
Turn in files       -
Parameters 			s: The string from which to create the substring.
					start: The start index of the substring in the string ’s’.
					len: The maximum length of the substring.
Return value 		The substring.
					NULL if the allocation fails.
External functs. 	malloc
Description 		Allocates (with malloc(3)) and returns a substring
					from the string ’s’.
					The substring begins at index ’start’ and is of
					maximum size ’len’.
*/

#include "../lib_liath.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	if (s == NULL)
		return (NULL);
	if (len == 0 || ft_strlen(s) < start)
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[start] != '\0' && len != 0)
	{
		str[i] = s[start];
		i++;
		start++;
		len--;
	}
	str[i] = '\0';
	return (str);
}
