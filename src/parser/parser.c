#include "../../inc/minishell.h"

bool	handle_pipe_node(t_command **current_cmd_node, \
t_command **head_cmd_node, t_data *data)
{
	t_command	*new_cmd_node;

	init_cmd_nodes(&new_cmd_node, head_cmd_node, current_cmd_node, data);
	if (data->tokens_list->type == PIPE)
	{
		if (data->tokens_list->next == NULL || \
		data->tokens_list->next->type != WORD)
			return (error_unexpected_token(data->tokens_list), false);
		data->tokens_list = data->tokens_list->next;
	}
	return (true);
}

bool	handle_redirection(t_command *current_cmd_node, t_data *data)
{
	if (data->tokens_list->next && data->tokens_list->next->type == WORD)
	{
		add_redirection(current_cmd_node, data->tokens_list->next->value, \
		data->tokens_list->type, data);
		data->tokens_list = data->tokens_list->next;
		return (true);
	}
	else
	{
		if (data->tokens_list->next && data->tokens_list->next->type != WORD)
			error_unexpected_token(data->tokens_list->next);
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

	current_cmd_node = NULL;
	head_cmd_node = NULL;
	while (data->tokens_list != NULL)
	{
		if (data->tokens_list->type == PIPE || current_cmd_node == NULL)
		{
			if (!handle_pipe_node(&current_cmd_node, &head_cmd_node, data))
				return (NULL);
			continue ;
		}
		if (data->tokens_list->type == WORD)
			add_argument(current_cmd_node, data->tokens_list->value);
		else if (check_if_redirect(data->tokens_list->type))
		{
			if (!handle_redirection(current_cmd_node, data))
				return (NULL);
		}
		data->tokens_list = data->tokens_list->next;
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
	free_tokens_list(data->tokens_list);
	set_index(data->command_list);
	return (true);
}
