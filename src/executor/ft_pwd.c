/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/15 15:52:16 by eandela       #+#    #+#                 */
/*   Updated: 2024/12/30 18:24:06 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_putstrendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

int	ft_pwd(char **args, t_env_list *env_list)
{
	char pwd[PATH_MAX];
	char *fail_pwd;
	
	if (!getcwd(pwd, PATH_MAX))
	{
		fail_pwd = ft_getenvp("PWD", env_list)->value;
		if (!fail_pwd)
			shell_exit(CWD_FAIL);
		ft_putstrendl_fd(fail_pwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	ft_putstrendl_fd(pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}