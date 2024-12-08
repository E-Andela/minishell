/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 12:16:40 by livliege      #+#    #+#                 */
/*   Updated: 2024/11/29 17:19:39 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_matching_quote(char *input, int start, int *num_quotes, char quote)
{
	int	i;

	i = start + 1;
	*num_quotes += 1;
	while (input[i] != '\0' && input[i] != quote)
		i++;
	if (input[i] == quote)
		*num_quotes += 1;
	return (i - start);
}

int	check_for_quotes(char *input)
{
	int	i;
	int	s;
	int	d;

	s = 0;
	d = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\"')
			i += find_matching_quote(input, i, &d, '\"');
		if (input[i] == '\'')
			i += find_matching_quote(input, i, &s, '\'');
		i++;
	}
	if ((d > 0 && d % 2 != 0) || (s > 0 && s % 2 != 0))
		return (0);
	return (1);
}

int	check_whitespace(char c)
{
	if (c == 32 || (c > 8 && c < 14))
		return (1);
	return (0);
}

int skip_spaces(char* input, int start)
{
	int	i;

	i = 0;
	while (check_whitespace(input[start + i]))
		i++;
	return (i);
}

t_token_type check_token(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '>')
		return (OUT_REDIRECT);
	if (c == '<')
		return (IN_REDIRECT);
	else
		return (UNSET);
}

// here we are going to handle |, >, >>, <, <<
int handle_token(char *input, int i, t_data *data)
{
	t_token_type	token;
	char	input_token[2];

	token = check_token(input[i]);
	if (token == OUT_REDIRECT && check_token(input[i + 1]) == OUT_REDIRECT)
	{
		if (!add_token(">>", OUT_APPEND, &data->tokens_list))
			return (-1);
		return (2);
	}
	else if (token == IN_REDIRECT && check_token(input[i + 1]) == IN_REDIRECT)
	{
		if (!add_token("<<", HERE_DOC, &data->tokens_list))
			return (-1);
		return (2);
	}
	else if (token)
	{
		input_token[0] = input[i];
		input_token[1] = '\0';
		if (!add_token(input_token, token, &data->tokens_list))
			return (-1);
		return (1);
	}	
	return (0);
}

int	handle_quotes(int start, char *input, char quote)
{
	int	i;

	i = 0;
	if (input[start + i] == quote)
	{
		i++;
		while (input[start + i] != quote && input[start + i])
			i++;
		i++;
	}
	return (i);
}


int check_words(char *input, int i, t_data *data)
{
	// here we are going to read the words, we're not going to handle them yet
	int				j;
	char			*token_value;
	// t_token_type 	token_type;

	j = 0;
	while (input[i + j] && !(check_token(input[i + j])))
	{
		j += handle_quotes(i + j, input, '\"');
		j += handle_quotes(i + j, input, '\'');
		if (check_whitespace(input[i + j]))
			break ;
		else
			j++;
	}
	token_value = ft_substr(input, i, j);
	// token_type = check_word_type(token_value, data);
	if (!add_token(token_value, WORD, &data->tokens_list))
		return (free(token_value), -1);
	return (free(token_value), j);
}

int tokenizer(char *input, t_data *data)
{
	int i;
	int j;

	i = 0;
	while (input[i] != '\0')
	{
		j = 0;
		i += skip_spaces(input, i);
		if (check_token(input[i]))
			j = handle_token(input, i, data);
		else
			j = check_words(input, i, data);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}
