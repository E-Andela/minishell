/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_and_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 14:53:36 by livliege      #+#    #+#                 */
/*   Updated: 2024/11/08 17:38:11 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_tokens(t_tokens *token_list)
{
	t_tokens	*temp_tokens;

	if (!token_list)
		return ;
	while (token_list)
	{
		temp_tokens = token_list->next;
		free(token_list->value);
		free(token_list);
		token_list = temp_tokens;
	}
	// tokens_list = NULL;
}

void	free_env_list(t_env_list *list)
{
	t_env_list	*temp_list;

	if (!list)
		return ;
	while (list)
	{
		temp_list = list->next;
		free(list->key);
		free(list->key_value);
		free(list);
		list = temp_list;
	}
	// list = NULL;
}

void	free_everything(t_data *data)
{
	// if (data->user_input)
	// 	free(data->user_input);

	// if (data->tokens_list)
	// {
	// 	free_tokens(data->tokens_list);
	// 	data->tokens_list = NULL;
	// }

	free_env_list(data->environment);
	data->environment = NULL;
	
	free(data);
}

void	exit_program(char *error_message, int errnbr)
{
	if (errnbr == 127)
		write(STDERR_FILENO, error_message, ft_strlen(error_message));
	else
		perror(error_message);
	exit(errnbr);
}
