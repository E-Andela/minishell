/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:13:50 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/16 15:13:50 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	handle_pipe_node(t_command **current_cmd_node, \
t_command **head_cmd_node, t_tokens *temp_list, t_data *data)
{
	t_command	*new_cmd_node;

	init_cmd_nodes(&new_cmd_node, head_cmd_node, current_cmd_node, data);
	if (temp_list->type == PIPE)
	{
		if (temp_list->next == NULL || \
		temp_list->next->type != WORD)
		{
			return (error_unexpected_token(temp_list), false);
		}
	}
	return (true);
}

bool	handle_redirection(t_command *current_cmd_node, t_tokens *temp_list, t_data *data)
{
	if (temp_list->next && temp_list->next->type == WORD)
	{
		add_redirection(current_cmd_node, temp_list->next->value, \
		temp_list->type, data);
		return (true);
	}
	else
	{
		if (temp_list->next && temp_list->next->type != WORD)
			error_unexpected_token(temp_list->next);
		else
			ft_putstr_fd("minishell: syntax error near \
unexpected token `newline'\n", STDERR_FILENO);
		return (false);
	}
}

t_command	*parse_tokens(t_data *data)
{
	t_command	*current_cmd_node;
	t_command	*head_cmd_node;
	t_tokens	*temp_list;

	current_cmd_node = NULL;
	head_cmd_node = NULL;
	temp_list = data->tokens_list;
	while (temp_list != NULL)
	{
		if (temp_list->type == PIPE || current_cmd_node == NULL)
		{
			if (!handle_pipe_node(&current_cmd_node, &head_cmd_node, temp_list, data))
				return (NULL);
		}
		if (temp_list->type == WORD)
			add_argument(current_cmd_node, temp_list->value);
		if (check_if_redirect(temp_list->type))
		{
			if (!handle_redirection(current_cmd_node, temp_list, data))
				return (NULL);
		}
		temp_list = temp_list->next;
	}
	return (head_cmd_node);
}

int	parser(t_data *data)
{
	t_command	*head_cmd_node;

	head_cmd_node = NULL;
	if (data->tokens_list == NULL)
		exit_program(ERR_TOKEN, errno, data);
	if (data->tokens_list->index == 0 && data->tokens_list->type == PIPE)
		return (error_unexpected_token(data->tokens_list), false);
	head_cmd_node = parse_tokens(data);
	if (head_cmd_node == NULL)
		return (false);
	data->command_list = head_cmd_node;
	set_index(data->command_list);
	free_tokens_list(data->tokens_list);
	data->tokens_list = NULL;
	print_cmd_list(data->command_list);
	return (true);
}
