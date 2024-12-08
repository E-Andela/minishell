/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 15:03:02 by livliege      #+#    #+#                 */
/*   Updated: 2024/09/17 17:19:17 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION

The calloc() function allocates memory for an array of  nmemb  elements
of  size bytes each and returns a pointer to the allocated memory.  The
memory is set to zero.  If nmemb or size is 0,  then  calloc()  returns
either  NULL,  or a unique pointer value that can later be successfully
passed to free().  If the multiplication of nmemb and size would result
in  integer  overflow, then calloc() returns an error.  By contrast, an
integer overflow would not be detected in the following  call  to  mal‐
loc(),  with the result that an incorrectly sized block of memory would
be allocated:

malloc(nmemb * size);

RETURN VALUE

The malloc() and calloc() functions return a pointer to  the  allocated
memory,  which  is  suitably  aligned for any built-in type.  On error,
these functions return NULL.  NULL may also be returned by a successful
call  to  malloc() with a size of zero, or by a successful call to cal‐
loc() with nmemb or size equal to zero.

The free() function returns no value.
*/


#include "../lib_liath.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && (nmemb * size) / size != nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}
