/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livliege <livliege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:14:54 by marvin            #+#    #+#             */
/*   Updated: 2024/02/22 13:46:56 by livliege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function name   	ft_strtrim
Prototype       	char *ft_strtrim(char const *s1, char const *set);
Turn in files   	-
Parameters      	s1: The string to be trimmed.
                	set: The reference set of characters to trim.
Return value 		The trimmed string.
					NULL if the allocation fails.
External functs		malloc
Description 		Allocates (with malloc(3)) and returns a copy of
					’s1’ with the characters specified in ’set’ removed
					from the beginning and the end of the string.
*/

#include "../lib_liath.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*trimmed_str;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[i]))
		i++;
	while (ft_strchr(set, s1[j]))
		j--;
	len = (j - i + 1);
	trimmed_str = ft_substr(s1, i, len);
	if (trimmed_str == NULL)
		return (NULL);
	return (trimmed_str);
}
