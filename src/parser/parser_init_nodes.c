/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_init_nodes.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:13:46 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/16 15:13:47 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_command	*init_command_node(void)
{
	t_command	*cmd_node;

	cmd_node = (t_command *)malloc(sizeof(t_command));
	if (cmd_node == NULL)
		return (NULL);
	cmd_node->args = NULL;
	cmd_node->redirections = NULL;
	cmd_node->next = NULL;
	cmd_node->prev = NULL;
	return (cmd_node);
}

t_redirections	*init_redirection_node(char *file, t_token_type type)
{
	t_redirections	*redir;

	redir = (t_redirections *)malloc(sizeof(t_redirections));
	if (redir == NULL)
		return (NULL);
	redir->file = ft_strdup(file);
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

void	init_cmd_nodes(t_command **new_cmd_node, t_command **head_cmd_node, \
t_command **current_cmd_node, t_data *data)
{
	*new_cmd_node = init_command_node();
	if (*new_cmd_node == NULL)
		exit_program(ERR_MALLOC, errno, data);
	if (*head_cmd_node == NULL)
		*head_cmd_node = *new_cmd_node;
	if (*current_cmd_node != NULL)
	{
		(*current_cmd_node)->next = *new_cmd_node;
		(*new_cmd_node)->prev = *current_cmd_node;
	}
	*current_cmd_node = *new_cmd_node;
}
