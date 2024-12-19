#include "../../inc/minishell.h"

// t_vector *expand_exit_code(t_vector *vector, int exit_code, t_data *data) 
// {
// 	char *exit_str;
// 	int	i;

// 	exit_str = ft_itoa(exit_code);
// 	if (!exit_str)
// 		exit_program(ERR_MALLOC, errno);
// 	i = 0;
// 	while (exit_str[i] != '\0')
// 	{
// 		vector_add_char(vector, exit_str[i], data);
// 		i++;
// 	}
// 	free(exit_str);
// 	return (vector);
// }

t_vector	*expand_exit_code(t_vector *vector, t_data *data)
{
	vector_add_char(vector, 'E', data);
	vector_add_char(vector, 'X', data);
	vector_add_char(vector, 'I', data);
	vector_add_char(vector, 'T', data);
	vector_add_char(vector, '-', data);
	vector_add_char(vector, 'C', data);
	vector_add_char(vector, 'O', data);
	vector_add_char(vector, 'D', data);
	vector_add_char(vector, 'E', data);
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
		expand_exit_code(vector, data);
		(*i)++;
		return ;
	}
	if (token_value[*i] == '\'' || token_value[*i] == '\"' || check_whitespace(token_value[*i]) || token_value[*i] == '\0')
	{
		vector_add_char(vector, '$', data);
		while (check_whitespace(token_value[*i]))
		{
			vector_add_char(vector, token_value[*i], data);
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
			vector_add_char(vector, env_key_value[j], data);
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
			vector_add_char(vector, token_value[*i], data);
			(*i)++;
		}
	}
	(*i)++;
}

void	expand_single_quotes(t_vector *vector, int *i, char *token_value, t_data *data)
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

void	expand_token(char **token_value, t_data *data)
{
	int			i;
	t_vector	vector;

	vector_init(&vector, data);
	i = 0;
	while ((*token_value)[i] != '\0')
	{
		if ((*token_value)[i] == '\'' || (*token_value)[i] == '\"' || (*token_value)[i] == '$')
			expander(&vector, &i, *token_value, data);
		else
		{
			vector_add_char(&vector, (*token_value)[i], data);
			i++;
		}
	}
	vector_add_char(&vector, '\0', data);
	free(*token_value);
	*token_value = ft_strdup(vector.value);
	free(vector.value);
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
			c = (*token_value)[i];
			i++;
			while ((*token_value)[i] != c && (*token_value)[i] != '\0')
			{
				vector_add_char(&vector, (*token_value)[i], data);
				i++;
			}
			if ((*token_value)[i] == c && (*token_value)[i] != '\0')
				i++;
		}
		else
		{
			vector_add_char(&vector, (*token_value)[i], data);
			i++;
		}
	}
	vector_add_char(&vector, '\0', data);
	free(*token_value);
	*token_value = ft_strdup(vector.value);
	free(vector.value);
}
