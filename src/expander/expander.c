#include "../../inc/minishell.h"

t_vector	*expand_exit_code(t_vector *vector)
{
	vector_add_char(vector, 'E');
	vector_add_char(vector, 'X');
	vector_add_char(vector, 'I');
	vector_add_char(vector, 'T');
	vector_add_char(vector, '-');
	vector_add_char(vector, 'C');
	vector_add_char(vector, 'O');
	vector_add_char(vector, 'D');
	vector_add_char(vector, 'E');
	return (vector);
}

void	expand_env_variable(t_vector *vector, int *i, char *token_value, t_data *data)
{
	char	*env_key;
	char	*env_key_value;
	int		j;

	(*i)++;
	if (token_value[*i] == '?')
	{
		expand_exit_code(vector);
		(*i)++;
		return ;
	}
	if (token_value[*i] == '\'' || token_value[*i] == '\"' || check_whitespace(token_value[*i]) || token_value[*i] == '\0')
	{
		vector_add_char(vector, '$');
		while (check_whitespace(token_value[*i]))
		{
			vector_add_char(vector, token_value[*i]);
			(*i)++;
		}
		return ;
	}
	env_key = get_environment_key(token_value, i, data);
	env_key_value = get_environment_key_values(data, env_key);
	if (env_key_value == NULL)
		return ;
	else
	{
		j = 0;
		while (env_key_value[j] != '\0')
		{
			vector_add_char(vector, env_key_value[j]);
			j++;
		}
	}
}

void	expand_double_quotes(t_vector *vector, int *i, char *token_value, t_data *data)
{
	(*i)++;
	while (token_value[(*i)] != '\"')
	{
		if (token_value[(*i)] == '$')
			expand_env_variable(vector, i, token_value, data);
		else
		{
			vector_add_char(vector, token_value[*i]);
			(*i)++;
		}
	}
	(*i)++;
}

void	expand_single_quotes(t_vector *vector, int *i, char *token_value)
{
	(*i)++;
	while (token_value[*i] != '\'')
	{
		vector_add_char(vector, token_value[*i]);
		(*i)++;
	}
	(*i)++;
}

void	expander(t_vector *vector, int *i, char *token_value, t_data *data)
{
	if (token_value[*i] == '\'')
		expand_single_quotes(vector, i, token_value);
	if (token_value[*i] == '\"')
		expand_double_quotes(vector, i, token_value, data);
	if (token_value[*i] == '$')
		expand_env_variable(vector, i, token_value, data);
}

void	expand_token(char **token_value, t_data *data)
{
	int			i;
	t_vector	vector;

	vector_init(&vector);
	i = 0;
	while ((*token_value)[i] != '\0')
	{
		if ((*token_value)[i] == '\'' || (*token_value)[i] == '\"' || (*token_value)[i] == '$')
			expander(&vector, &i, *token_value, data);
		else if ((*token_value)[i] != '\0')
		{
			vector_add_char(&vector, (*token_value)[i]);
			i++;
		}
	}
	vector_add_char(&vector, '\0');
	free(*token_value);
	*token_value = ft_strdup(vector.value);
	free(vector.value);
}
