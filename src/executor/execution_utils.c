/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/05 21:35:24 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/05 21:39:45 by eandela       ########   odam.nl         */
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
