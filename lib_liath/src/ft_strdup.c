/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 20:31:06 by livliege      #+#    #+#                 */
/*   Updated: 2024/09/17 17:14:18 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
       The  strdup()  function  returns a pointer to a new string 
	   which is a duplicate of the string s.  Memory for the new
       string is obtained with malloc(3), and can be freed with free(3).

       The strndup() function is similar, but copies at most n bytes.  
	   If s is longer than n, only n bytes are copied,  and
       a terminating null byte ('\0') is added.

       strdupa()  and strndupa() are similar,
	   but use alloca(3) to allocate the buffer.
	   They are available only when using
       the GNU GCC suite, and suffer from the same limitations 
	   described in alloca(3).

RETURN VALUE
       On success, the strdup() function returns a pointer to the 
	   duplicated string. 
       It returns NULL if insufficient memory was available, 
	   with errno set to indicate the cause of the error.
*/


#include "../lib_liath.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
