/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 15:23:22 by livliege      #+#    #+#                 */
/*   Updated: 2024/09/17 17:19:25 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
       The  bzero()  function erases the data in the n bytes of the memory 
	   starting at the location pointed to by s,
       by writing zeros (bytes containing '\0') to that area.

       The explicit_bzero() function performs the same task as bzero().  
	   It differs from bzero() in that it  guaran‐
       tees  that compiler optimizations will not remove the erase 
	   operation if the compiler deduces that the opera‐
       tion is "unnecessary".

RETURN VALUE
       None.
*/

#include "../lib_liath.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

