/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 14:02:11 by livliege      #+#    #+#                 */
/*   Updated: 2024/09/17 17:19:12 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
       The memset() function fills the first n bytes of the memory area pointed 
	   to by s with the constant byte c.

RETURN VALUE
       The memset() function returns a pointer to the memory area s.
*/

#include "../lib_liath.h"

void	*ft_memset(void *s, int c, size_t n)
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
