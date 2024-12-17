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
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	trimmed_arg = ft_strtrim(arg, "\'\"");
	new_args[count] = ft_strdup(trimmed_arg);
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

void	add_redirection(t_command *cmd, char *file, t_token_type type, t_data *data)
{
	t_redirections	*redir;
	t_redirections	*current;

	redir = init_redirection_node(file, type);
	if (redir == NULL)
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

void	parser(t_data *data)
{
	t_command	*current_cmd_node;
	t_command	*head_cmd_node;
	t_command	*new_cmd;

	current_cmd_node = NULL;
	head_cmd_node = NULL;
	if (data->tokens_list == NULL)
		exit_program(ERR_TOKEN, errno, data);
	if (data->tokens_list->index == 0 && data->tokens_list->type == PIPE)
	{
		unexpected_token_error(data, data->tokens_list);
		return ;
	}
	while (data->tokens_list != NULL)
	{
		if (data->tokens_list->type == PIPE || current_cmd_node == NULL)
		{
			new_cmd = init_command_node();
			if (new_cmd == NULL)
				exit_program(ERR_MALLOC, errno, data);
			if (head_cmd_node == NULL)
				head_cmd_node = new_cmd;
			if (current_cmd_node != NULL)
			{
				current_cmd_node->next = new_cmd;
				new_cmd->prev = current_cmd_node;
			}
			current_cmd_node = new_cmd;
			if (data->tokens_list->type == PIPE)
			{
				data->tokens_list = data->tokens_list->next;
				if (data->tokens_list == NULL)
					break ;
				continue ;
			}
		}
		if (data->tokens_list->type == WORD)
			add_argument(current_cmd_node, data->tokens_list->value);
		else if (data->tokens_list->type == OUT_REDIRECT || data->tokens_list->type == IN_REDIRECT || data->tokens_list->type == OUT_APPEND || data->tokens_list->type == HERE_DOC)
		{
			if (data->tokens_list->next)
			{
				add_redirection(current_cmd_node, data->tokens_list->next->value, data->tokens_list->type, data);
				data->tokens_list = data->tokens_list->next;
			}
			else
			{
				unexpected_token_error(data, data->tokens_list);
				return ;
			}
		}
		data->tokens_list = data->tokens_list->next;
	}
	data->command_list = head_cmd_node;
}
