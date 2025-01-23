/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:13:59 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/23 11:09:02 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_token(char *input, int i, t_data *data)
{
	t_token_type	token;
	char			input_token[2];

	token = check_token(input[i]);
	if (token == OUT_REDIRECT && check_token(input[i + 1]) == OUT_REDIRECT)
	{
		add_token(">>", OUT_APPEND, &data->tokens_list, data);
		return (2);
	}
	else if (token == IN_REDIRECT && check_token(input[i + 1]) == IN_REDIRECT)
	{
		add_token("<<", HERE_DOC, &data->tokens_list, data);
		return (2);
	}
	else if (token)
	{
		input_token[0] = input[i];
		input_token[1] = '\0';
		if (token == PIPE)
			data->pipe_count ++;
		add_token(input_token, token, &data->tokens_list, data);
		return (1);
	}
	return (0);
}

int	skip_to_next_quote(int start, char *input, char quote)
{
	int	i;

	i = 0;
	if (input[start + i] == quote)
	{
		i++;
		while (input[start + i] && input[start + i] != quote)
			i++;
		i++;
	}
	return (i);
}

int	handle_words(char *input, int start, t_data *data)
{
	int				j;
	char			*token_value;

	j = 0;
	while (input[start + j] && !(check_token(input[start + j])))
	{
		j += skip_to_next_quote(start + j, input, '\"');
		j += skip_to_next_quote(start + j, input, '\'');
		if (check_whitespace(input[start + j]))
			break ;
		else
			j++;
	}
	token_value = ft_substr(input, start, j);
	if (!token_value)
		exit_program(ERR_MALLOC, errno, data);
	add_token(token_value, WORD, &data->tokens_list, data);
	free(token_value);
	return (j);
}

void	tokenizer(char *input, t_data *data)
{
	int	i;
	int	j;

	if (!check_for_quotes(input))
	{
		data->exit_code = 2;
		exit_program(ERR_QUOTES, 2, data);
	}
	i = 0;
	while (input[i] != '\0')
	{
		j = 0;
		i += skip_spaces(input, i);
		if (check_token(input[i]) != UNSET)
			j = handle_token(input, i, data);
		else
			j = handle_words(input, i, data);
		i += j;
	}
}
