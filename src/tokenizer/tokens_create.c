/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens_create.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:14:03 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/16 15:14:03 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tokens	*create_token_node(char *input, \
t_token_type token_type, int index, t_data *data)
{
	t_tokens	*new_token;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new_token)
		exit_program(ERR_MALLOC, errno, data);
	new_token->value = ft_strdup(input);
	if (!new_token->value)
		exit_program(ERR_MALLOC, errno, data);
	new_token->type = token_type;
	new_token->index = index;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

t_tokens	*get_last_token(t_tokens *token_list)
{
	if (!token_list)
		return (NULL);
	while (token_list->next)
		token_list = token_list->next;
	return (token_list);
}

void	add_token(char *input, t_token_type token_type, \
t_tokens **token_list, t_data *data)
{
	t_tokens	*new_token;
	t_tokens	*last_token;
	static int	index = 0;

	if (!(*token_list))
		index = 0;
	new_token = create_token_node(input, token_type, index++, data);
	if (!new_token)
		exit_program(ERR_MALLOC, errno, data);
	if (!(*token_list))
	{
		new_token->next = NULL;
		new_token->prev = NULL;
		*token_list = new_token;
	}
	else
	{
		last_token = get_last_token(*token_list);
		new_token->prev = last_token;
		last_token->next = new_token;
	}
}
