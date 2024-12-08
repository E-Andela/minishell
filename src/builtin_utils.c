/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/07 16:12:00 by eandela       #+#    #+#                 */
/*   Updated: 2024/12/08 22:02:22 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (1);
	// if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
	// 	return (1);
	if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (1);
	// if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
	// 	return (1);
	return (0);
}

int execute_builtin(char **args, t_env_list *env_list)
{
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		return (ft_echo(args));
	if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return (ft_pwd());
	// if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
	// 	return (ft_cd(args));
	if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		return (ft_export(args, env_list));
	if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		return (ft_unset(args, &env_list));
	if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		return (ft_env(ft_ll2arr(env_list)));
	// if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
	// 	return (ft_exit(args));
	return (0);
}

