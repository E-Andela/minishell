/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livliege <livliege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:25:38 by livliege          #+#    #+#             */
/*   Updated: 2024/02/22 13:46:17 by livliege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function name       ft_putstr_fd
Prototype           void ft_putstr_fd(char *s, int fd);
Turn in files       -
Parameters          s: The string to output.
                    fd: The file descriptor on which to write.
Return value        None
External functs.    write
Description         Outputs the string ’s’ to the given file descriptor.
*/

#include "../lib_liath.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
