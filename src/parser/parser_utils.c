/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:13:48 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/16 15:13:48 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	copy_arguments(char **new_args, char **old_args, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		new_args[i] = old_args[i];
		i++;
	}
}

void	add_argument(t_command *cmd, char *arg)
{
	int		count;
	char	**new_args;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_args = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		exit_program(ERR_MALLOC, errno, NULL);
	copy_arguments(new_args, cmd->args, count);
	new_args[count] = ft_strdup(arg);
	if (!new_args[count])
		exit_program(ERR_MALLOC, errno, NULL);
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

void	add_redirection(t_command *cmd, char *file, \
t_token_type type, t_data *data)
{
	t_redirections	*redir;
	t_redirections	*current;

	redir = init_redirection_node(file, type);
	if (!redir)
		exit_program(ERR_MALLOC, errno, data);
	if (!cmd->redirections)
		cmd->redirections = redir;
	else
	{
		current = cmd->redirections;
		while (current->next)
			current = current->next;
		current->next = redir;
	}
}

void	set_index(t_command *cmd_list)
{
	int	i;

	i = 0;
	while (cmd_list)
	{
		cmd_list->index = i;
		cmd_list = cmd_list->next;
		i++;
	}
}

bool	check_if_redirect(t_token_type type)
{
	if (type == OUT_REDIRECT || type == IN_REDIRECT || \
	type == OUT_APPEND || type == HERE_DOC)
		return (true);
	else
		return (false);
}
