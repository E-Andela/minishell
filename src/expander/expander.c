#include "../../inc/minishell.h"

t_vector	*expand_exit_code(t_vector *vector, t_data *data)
{
	char	*exit_code;
	int		i;

	exit_code = ft_itoa(data->exit_code);
	if (!exit_code)
		exit_program(ERR_MALLOC, errno, data);
	i = 0;
	while (exit_code[i] != '\0')
	{
		vector_add_char(vector, exit_code[i], data);
		i++;
	}
	free(exit_code);
	return (vector);
}

void	copy_env_key_value(char *env_key_value, t_vector *vector, t_data *data)
{
	int	j;

	j = 0;
	while (env_key_value[j] != '\0')
	{
		vector_add_char(vector, env_key_value[j], data);
		j++;
	}
}


void	expand_env_variable(t_vector *vector, int *i, \
char *token_value, t_data *data)
{
	char	*env_key;
	char	*env_key_value;

	(*i)++;
	if (token_value[*i] == '?')
	{
		expand_exit_code(vector, data);
		(*i)++;
		return ;
	}
	if (token_value[*i] == '\'' || token_value[*i] == '\"' || \
	check_whitespace(token_value[*i]) || token_value[*i] == '\0')
	{
		vector_add_char(vector, '$', data);
		while (check_whitespace(token_value[*i]))
			vector_add_char(vector, token_value[*i++], data);
		return ;
	}
	env_key = get_environment_key(token_value, i, data);
	env_key_value = get_environment_key_values(data, env_key);
	if (env_key_value == NULL)
		return ;
	else
		copy_env_key_value(env_key_value, vector, data);
}

void	expand_double_quotes(t_vector *vector, int *i, \
char *token_value, t_data *data)
{
	(*i)++;
	while (token_value[(*i)] != '\"')
	{
		if (token_value[(*i)] == '$')
			expand_env_variable(vector, i, token_value, data);
		else
		{
			vector_add_char(vector, token_value[*i], data);
			(*i)++;
		}
	}
	(*i)++;
}

void	expand_single_quotes(t_vector *vector, int *i, \
char *token_value, t_data *data)
{
	(*i)++;
	while (token_value[*i] != '\'')
	{
		vector_add_char(vector, token_value[*i], data);
		(*i)++;
	}
	(*i)++;
}

void	expander(t_vector *vector, int *i, char *token_value, t_data *data)
{
	if (token_value[*i] == '\'')
		expand_single_quotes(vector, i, token_value, data);
	if (token_value[*i] == '\"')
		expand_double_quotes(vector, i, token_value, data);
	if (token_value[*i] == '$')
		expand_env_variable(vector, i, token_value, data);
}

bool	expand_token(t_tokens *token_node, char **token_value, t_data *data)
{
	int			i;
	t_vector	vector;

	vector_init(&vector, data);
	i = 0;
	while ((*token_value)[i] != '\0')
	{
		if ((*token_value)[i] == '\'' || \
		(*token_value)[i] == '\"' || (*token_value)[i] == '$')
			expander(&vector, &i, *token_value, data);
		else
			vector_add_char(&vector, (*token_value)[i++], data);
	}
	vector_add_char(&vector, '\0', data);
	if (ft_strlen(vector.value) == 0)
	{
		if (ambiguous_redir(token_node, *token_value, data))
			return (false);
	}
	free(*token_value);
	*token_value = ft_strdup(vector.value);
	if (*token_value == NULL)
		shell_exit(MALLOC_FAIL);
	free(vector.value);
	return (true);
}

void	remove_quotes(char **token_value, t_data *data)
{
	int			i;
	char		c;
	t_vector	vector;

	vector_init(&vector, data);
	i = 0;
	while ((*token_value)[i] != '\0')
	{
		if ((*token_value)[i] == '\'' || (*token_value)[i] == '\"')
		{
			c = (*token_value)[i++];
			while ((*token_value)[i] != c && (*token_value)[i] != '\0')
				vector_add_char(&vector, (*token_value)[i++], data);
			if ((*token_value)[i] == c && (*token_value)[i] != '\0')
				i++;
		}
		else
			vector_add_char(&vector, (*token_value)[i++], data);
	}
	vector_add_char(&vector, '\0', data);
	free(*token_value);
	*token_value = ft_strdup(vector.value);
	if (*token_value == NULL)
		shell_exit(MALLOC_FAIL);
	free(vector.value);
}
