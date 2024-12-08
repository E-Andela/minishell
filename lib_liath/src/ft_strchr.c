/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livliege <livliege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:07:21 by livliege          #+#    #+#             */
/*   Updated: 2024/02/22 13:46:24 by livliege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
       The strchr() function returns a pointer to the first occurrence of the 
	   character c in the string s.

       Here "character" means "byte"; these functions do not work with wide or 
	   multibyte characters.

RETURN VALUE
       The strchr() and strrchr() functions return a pointer to the matched 
	   character or  NULL  if  the  character  is  not
       found.   The  terminating null byte is considered part of the string, 
	   so that if c is specified as '\0', these func‐
       tions return a pointer to the terminator.

       The strchrnul() function returns a pointer to the matched character, 
	   or a pointer to the null byte at the end  of  s
       (i.e., s+strlen(s)) if the character is not found.
*/

#include "../lib_liath.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	ch;

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
