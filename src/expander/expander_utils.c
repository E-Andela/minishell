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

char	*get_environment_key(char	*input, int *i, t_data *data)
{
	int		start;
	char	*key;

	start = (*i);
	while (input[(*i)] && (ft_isalnum(input[(*i)]) || input[(*i)] == '_'))
		(*i)++;
	key = ft_substr(input, start, (*i) - start);
	if (!key)
		shell_exit(MALLOC_FAIL);
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

bool	is_redirect(t_token_type type)
{
	if (type == IN_REDIRECT || type == OUT_REDIRECT || type == OUT_APPEND)
		return (true);
	return (false);
}

bool	ambiguous_redir(t_tokens *current_node, char *token_value, t_data *data)
{
	t_tokens *prev_node;

	if (!current_node->prev)
		return (true);
	prev_node = current_node->prev;
	if (!is_redirect(prev_node->type))
		return (false);
	error_ambiguous_redirect(current_node);
	return (true);
}

bool	expander_check(t_tokens *tokens_list, t_data *data)
{
	while (tokens_list != NULL)
	{
		if ((tokens_list->type == WORD) && (check_dollar_sign(tokens_list->value) == true))
		{
			if (!expand_token(tokens_list, &tokens_list->value, data))
			{
				return (false);
			}
		}
		else if ((tokens_list->type == WORD) && (check_for_quotes(tokens_list->value)))
			remove_quotes(&tokens_list->value, data);
		tokens_list = tokens_list->next;
	}
	return (true);
}
