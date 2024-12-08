/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livliege <livliege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:50:51 by livliege          #+#    #+#             */
/*   Updated: 2024/02/22 13:44:45 by livliege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
       These  functions  check  whether c, which must have the value of an un‐
       signed char or EOF, falls into a certain character class  according  to
       the  specified  locale.

isalnum()
        checks for an alphanumeric character; it is equivalent to 
		(isalpha(c) || isdigit(c)).
			  
RETURN VALUE
       The  values  returned  are  nonzero  if  the character c falls into the
       tested class, and zero if not.
*/

#include "../lib_liath.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || \
		(c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
