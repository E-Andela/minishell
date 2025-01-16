/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_environment.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:13:06 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/16 15:13:06 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
			return (temp->value);
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
