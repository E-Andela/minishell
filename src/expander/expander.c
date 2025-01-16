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
		if (ambiguous_redir(token_node))
			return (false);
	}
	free(*token_value);
	*token_value = ft_strdup(vector.value);
	if (*token_value == NULL)
		shell_exit(MALLOC_FAIL);
	free(vector.value);
	return (true);
}
