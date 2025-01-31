/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_lists.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 16:04:27 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/16 16:04:27 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_tokens_list(t_tokens *token_list)
{
	t_tokens	*next_node;

	while (token_list)
	{
		next_node = token_list->next;
		free(token_list->value);
		free(token_list);
		token_list = next_node;
	}
}

void	free_env_list(t_env_list *env_list)
{
	t_env_list	*next_node;

	while (env_list)
	{
		next_node = env_list->next;
		free(env_list->key);
		free(env_list->value);
		free(env_list);
		env_list = next_node;
	}
}

void	free_cmd_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_redirections(t_redirections *redirs)
{
	t_redirections	*next_node;

	while (redirs)
	{
		next_node = redirs->next;
		free(redirs->file);
		free(redirs);
		redirs = next_node;
	}
}

void	free_command_list(t_command *command_list)
{
	t_command	*next_node;

	if (!command_list)
		return ;
	while (command_list)
	{
		next_node = command_list->next;
		if (command_list->args)
		{
			free_cmd_args(command_list->args);
			command_list->args = NULL;
		}
		if (command_list->redirections)
		{
			free_redirections(command_list->redirections);
			command_list->redirections = NULL;
		}
		free(command_list);
		command_list = next_node;
	}
}
