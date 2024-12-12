/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:53:17 by marvin            #+#    #+#             */
/*   Updated: 2024/11/11 14:53:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_tokens	*create_token_node(char *input, t_token_type token_type, int index)
{
	t_tokens	*new_token;
	
	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	if (new_token == NULL)
		return (NULL);
	
	new_token->value = ft_strdup(input);
	new_token->type = token_type;
	new_token->index = index;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

t_tokens *get_last_token(t_tokens *token_list)
{
	if (!token_list)
		return (NULL);
	while (token_list->next)
		token_list = token_list->next;
	return (token_list);
}

int add_token(char *input, t_token_type token_type, t_tokens **token_list)
{
	t_tokens	*new_token;
	t_tokens	*last_token;
	static int	index = 0; 

	if (!(*token_list))
		index = 0;
	new_token = create_token_node(input, token_type, index++);
	if (new_token == NULL)
		return (0);
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
	return (1);
}


// add_token(token_value, WORD, &data->tokens_list);