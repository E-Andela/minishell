/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/15 15:52:16 by eandela       #+#    #+#                 */
/*   Updated: 2024/12/12 17:41:21 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_putstrendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

int	ft_pwd(void)
{
	char pwd[PATH_MAX];
	
	getcwd(pwd, PATH_MAX);
	if (!getcwd(pwd, PATH_MAX))
		return (EXIT_FAILURE);
	ft_putstrendl_fd(pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}