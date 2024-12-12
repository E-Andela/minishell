#include "../../inc/minishell.h"

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

int	skip_spaces(char *input, int start)
{
	int	i;

	i = 0;
	while (check_whitespace(input[start + i]))
		i++;
	return (i);
}

t_token_type	check_token(char c)
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
