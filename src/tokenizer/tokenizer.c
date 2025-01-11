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
		while (input[start + i] != quote && input[start + i])
			i++;
		i++;
	}
	return (i);
}

int	check_words(char *input, int start, t_data *data)
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
	return (free(token_value), j);
}

void	tokenizer(char *input, t_data *data)
{
	int	i;
	int	j;

	if (!check_for_quotes(input))
		exit_program(ERR_QUOTES, errno, data);
	if (data->tokens_list)
		free_tokens_list(data->tokens_list);
	i = 0;
	while (input[i] != '\0')
	{
		j = 0;
		i += skip_spaces(input, i);
		if (check_token(input[i]) != UNSET)
			j = handle_token(input, i, data);
		else
			j = check_words(input, i, data);
		i += j;
	}
}
