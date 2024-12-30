#include "../../inc/minishell.h"

void	add_argument(t_command *cmd, char *arg)
{
	int		count;
	int		i;
	char	**new_args;
	char	*trimmed_arg;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_args = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		exit_program(ERR_MALLOC, errno, NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[count] = ft_strdup(arg);
	if (!new_args[count])
		exit_program(ERR_MALLOC, errno, NULL);
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

void	add_redirection(t_command *cmd, char *file, t_token_type type, t_data *data)
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

int	parser(t_data *data)
{
	t_command	*current_cmd_node;
	t_command	*head_cmd_node;
	t_command	*new_cmd_node;

	if (data->command_list)
		free_command_list(data->command_list);
	current_cmd_node = NULL;
	head_cmd_node = NULL;
	if (data->tokens_list == NULL)
		exit_program(ERR_TOKEN, errno, data);
	if (data->tokens_list->index == 0 && data->tokens_list->type == PIPE)
	{
		error_unexpected_token(data->tokens_list);
		return (false);
	}
	while (data->tokens_list != NULL)
	{
		if (data->tokens_list->type == PIPE || current_cmd_node == NULL)
		{
			new_cmd_node = init_command_node();
			if (new_cmd_node == NULL)
				exit_program(ERR_MALLOC, errno, data);
			if (head_cmd_node == NULL)
				head_cmd_node = new_cmd_node;
			if (current_cmd_node != NULL)
			{
				current_cmd_node->next = new_cmd_node;
				new_cmd_node->prev = current_cmd_node;
			}
			current_cmd_node = new_cmd_node;
			if (data->tokens_list->type == PIPE)
			{
				if (data->tokens_list->next == NULL || data->tokens_list->next->type != WORD)
				{
					error_unexpected_token(data->tokens_list);
					return (false);
				}
				data->tokens_list = data->tokens_list->next;
				continue ;
			}
		}
		if (data->tokens_list->type == WORD)
			add_argument(current_cmd_node, data->tokens_list->value);
		else if (data->tokens_list->type == OUT_REDIRECT || data->tokens_list->type == IN_REDIRECT || data->tokens_list->type == OUT_APPEND || data->tokens_list->type == HERE_DOC)
		{
			if (data->tokens_list->next && data->tokens_list->next->type == WORD)
			{
				add_redirection(current_cmd_node, data->tokens_list->next->value, data->tokens_list->type, data);
				data->tokens_list = data->tokens_list->next;
			}
			else
			{
				if (data->tokens_list->next && data->tokens_list->next->type != WORD)
					error_unexpected_token(data->tokens_list->next);
				else
				{
					ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
					// error_unexpected_token(data->tokens_list);
				}
				return (false);
			}
		}
		data->tokens_list = data->tokens_list->next;
	}
	data->command_list = head_cmd_node;
	free_tokens_list(data->tokens_list);
	set_index(data->command_list);
	return (true);
}
