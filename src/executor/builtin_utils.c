/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/07 16:12:00 by eandela       #+#    #+#                 */
/*   Updated: 2024/12/21 14:27:57 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
		return (1);
	// if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
	// 	return (1);
	return (0);
}

int execute_builtin(char **args, t_env_list *env_list)
{
	if (ft_strncmp(args[0], "echo", ft_strlen("echo")) == 0)
		return (ft_echo(args));
	if (ft_strncmp(args[0], "pwd", ft_strlen("pwd")) == 0)
		return (ft_pwd());
	if (ft_strncmp(args[0], "cd", ft_strlen("cd")) == 0)
		return (ft_cd(args, env_list));
	if (ft_strncmp(args[0], "export", ft_strlen("export")) == 0)
		return (ft_export(args, env_list));
	if (ft_strncmp(args[0], "unset", ft_strlen("unset")) == 0)
		return (ft_unset(args, &env_list));
	if (ft_strncmp(args[0], "env", ft_strlen("env")) == 0)
		return (ft_env(ft_ll2arr(env_list)));
	// if (ft_strncmp(args[0], "exit", ft_strlen("exit")) == 0)
	// 	return (ft_exit(args));
	return (0);
}

