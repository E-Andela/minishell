/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 19:09:40 by livliege      #+#    #+#                 */
/*   Updated: 2024/09/17 17:14:29 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_liath.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
