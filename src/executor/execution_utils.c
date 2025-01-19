/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/05 21:35:24 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/19 18:52:01 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_cmds(t_command *cmd_list)
{
	int	i;

	i = 0;
	while (cmd_list)
	{
		i++;
		cmd_list = cmd_list->next;
	}
	return (i);
}

int	wait_for_children(t_command *cmd_list)
{
	int	status;

	status = 0;
	while (cmd_list)
	{
		waitpid(cmd_list->pid, &status, 0);
		cmd_list = cmd_list->next;
	}
	if (status == 2 && g_signal == SIGINT)
		return (130);
	if (status == 131 && g_signal == SIGQUIT)
		return (131);
	return (WEXITSTATUS(status));
}

void	check_if_directory(char *path, t_command *cmd_list)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_list->args[0], STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		exit(126);
	}
	if (ft_strchr(cmd_list->args[0], '/') && !path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_list->args[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit(127);
	}
	if (!path)
	{
		error_command_not_found(cmd_list->args[0]);
		exit(127);
	}
}
