#include "../../inc/minishell.h"

// here we are going to handle |, >, >>, <, <<
int	handle_token(char *input, int i, t_data *data)
{
	t_token_type	token;
	char			input_token[2];

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

// here we are going to read the words, we're not going to handle them yet
int	check_words(char *input, int i, t_data *data)
{
	int				j;
	char			*token_value;

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
	if (!add_token(token_value, WORD, &data->tokens_list))
		return (free(token_value), -1);
	return (free(token_value), j);
}

int	tokenizer(char *input, t_data *data)
{
	int	i;
	int	j;

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
