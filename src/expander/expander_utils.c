/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:12:54 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/23 13:33:51 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	check_dollar_sign(char	*str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

bool	is_redirect(t_token_type type)
{
	if (type == IN_REDIRECT || type == OUT_REDIRECT || type == OUT_APPEND)
		return (true);
	return (false);
}

bool	expander_check(t_tokens *tokens_list, t_data *data)
{
	while (tokens_list != NULL)
	{
		if ((tokens_list->type == WORD) && \
		(check_dollar_sign(tokens_list->value) == true))
		{
			if (!expand_token(tokens_list, &tokens_list->value, data))
			{
				return (false);
			}
		}
		else if ((tokens_list->type == WORD) && \
		(ft_strchr(tokens_list->value, '\'') || \
		ft_strchr(tokens_list->value, '\"')))
		{
			remove_quotes(&tokens_list->value, data);
		}
		tokens_list = tokens_list->next;
	}
	return (true);
}
