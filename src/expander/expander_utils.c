#include "../../inc/minishell.h"

char	*get_environment_key_values(t_data *data, char	*input)
{
	t_env_list	*temp;
	int			len;

	temp = data->environment;
	len = ft_strlen(input);
	while (temp != NULL)
	{
		if (ft_strncmp(input, temp->key, len) == 0 && temp->key[len] == '\0')
			return (temp->key_value);
		temp = temp->next;
	}
	return (NULL);
}

char	*get_environment_key(char	*input, int *i)
{
	int		start;
	char	*key;

	start = (*i);
	while (input[(*i)] && (ft_isalnum(input[(*i)]) || input[(*i)] == '_'))
		(*i)++;
	key = ft_substr(input, start, (*i) - start);
	if (key == NULL)
		exit_program("malloc", errno);
	return (key);
}

bool	check_dollar_sign(char	*str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

void	expander_check(t_tokens *tokens_list, t_data *data)
{
	while (tokens_list != NULL)
	{
		if ((tokens_list->type == WORD) && (check_dollar_sign(tokens_list->value) == true))
			expand_token(&tokens_list->value, data);
		tokens_list = tokens_list->next;
	}
}
