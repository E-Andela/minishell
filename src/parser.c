/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:45:45 by marvin            #+#    #+#             */
/*   Updated: 2024/11/25 16:45:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


// The first thing the parser does is loop through the lexer list until it encounters a pipe. 
// It then takes all the nodes before the pipe as one command, and creates a node in the t_simple_cmds struct. 
// If it doesn't find a pipe it takes all the (remaining) nodes as one command.

// The parser takes the t_tokens list (left) and converts it into the t_simple_cmds list (right)

// - For each command it first checks for redirections, which it stores in the *redirections linked list, 
// 		which holds both the token and the filename or delimiter in the case of a heredoc. 
// - When the nodes are added to the *redirections list, they are deleted from the lexer list. 
// - Next it checks if the first word is a builtin, in which case it stores a function pointer to the corresponding function, more on this bellow. 
// - As the redirections have been removed from the lexer list, the parser can easily combines all remaining words into a 2D array, which is a required execve argument. 
// - It also makes it easier to handle situations where the words may be seperated by redirections, for example:

// cat > file -e

// As > and file are already deleted from the lexer list when they are added to the redirections list, all that remains is cat and -e. 
// Which then can easily be added into an array.

// This process is repeated until the end of the lexer list.


// 		ls -l | echo a > file


t_command	*init_command_node(void)
{
	t_command *cmd_node;

	cmd_node = (t_command *)malloc(sizeof(t_command));
	if (cmd_node == NULL)
		return (NULL);
	cmd_node->args = NULL;
	cmd_node->redirections = NULL;
	cmd_node->next = NULL;
	cmd_node->prev = NULL;
	return (cmd_node);
}


t_redirections *init_redirection_node(char *file, t_token_type type)
{
    t_redirections *redir;
	redir = (t_redirections *)malloc(sizeof(t_redirections));
    if (redir == NULL)
        return (NULL);
    redir->file = ft_strdup(file);
    redir->type = type;
    redir->next = NULL;
    return (redir);
}

void add_argument(t_command *cmd, char *arg)
{
    int count;
	int i;
	char **new_args;

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
    new_args[count] = ft_strdup(arg);
    new_args[count + 1] = NULL;
    free(cmd->args);
    cmd->args = new_args;
}

void add_redirection(t_command *cmd, char *file, t_token_type type)
{
    t_redirections *redir;
	t_redirections *current;

	redir = init_redirection_node(file, type);
    if (redir == NULL)
        return (exit_program(ERR_MALLOC, errno));

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


void parser(t_data *data)
{
    t_command *current_cmd_node;
    t_command *head_cmd_node;
    t_command *new_cmd;

	current_cmd_node = NULL;
    head_cmd_node = NULL;
	if (data->tokens_list == NULL)
		exit_program(ERR_TOKEN, errno);
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
                return (exit_program(ERR_MALLOC, errno));
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
                    break; // Prevent accessing NULL
                continue;
            }
        }
        if (data->tokens_list->type == WORD)
        {
            add_argument(current_cmd_node, data->tokens_list->value);
        }
        else if (data->tokens_list->type == OUT_REDIRECT || data->tokens_list->type == IN_REDIRECT ||
                 data->tokens_list->type == OUT_APPEND || data->tokens_list->type == HERE_DOC)
        {
            if (data->tokens_list->next)
            {
                add_redirection(current_cmd_node, data->tokens_list->next->value, data->tokens_list->type);
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


// vind ik een woord - 2d aray add back functie met strdup
// vind ik een special token + word - redirect node maken + filename
// PIPE!!!! met recursion is dubbel points! en een kusje

