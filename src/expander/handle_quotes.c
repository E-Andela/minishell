#include "../../inc/minishell.h"

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
