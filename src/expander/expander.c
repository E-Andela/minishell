/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:45:22 by livliege      #+#    #+#                 */
/*   Updated: 2024/12/12 14:45:22 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_realloc_copy(char *str, unsigned int old_size, unsigned int new_size)
{
	char	*new_str;
	char	*temp;
	unsigned int i;

	new_str = malloc(new_size);
	if (new_str == NULL)
		return (NULL);
	if (new_size < old_size)
	old_size = new_size;
	temp = str;
	i = 0;
	while (i < old_size)
	{
		new_str[i] = temp[i];
		i++;
	}
	free(str);
	return (new_str);
}

void *ft_realloc(void *str, unsigned int old_size, unsigned int new_size)
{
	char *new_str;

	if (str == NULL)
	{
		str = malloc(new_size);
		if (str == NULL)
			return (NULL);
		return (str);
	}
	if (new_size == old_size)
		return (str);
	if (new_size == 0 && str != NULL)
		return (free(str), NULL);
	if (!(new_str = ft_realloc_copy(str, old_size, new_size)))
		return (free(str), NULL);
	return (new_str);
}

static void vector_resize(t_vector *vector, int new_capacity)
{
    char	*resized_vector;

	resized_vector = ft_realloc(vector->value, vector->capacity, new_capacity);
	if (resized_vector == NULL)
		exit(EXIT_FAILURE);
	// printf("vector_resize: %d to %d\n", vector->capacity, new_capacity);
	// free(vector->value); we already free this as *ptr in realloc?
	vector->value = resized_vector;
	vector->capacity = new_capacity;
	// free(resized_vector);
}

void vector_init(t_vector *vector)
{
    vector->capacity = VECTOR_INIT_CAPACITY;
    vector->total = 0;
    vector->value = malloc(sizeof(char) * vector->capacity);
}

void vector_add_char(t_vector *vector, char c)
{
    if (vector->capacity == vector->total)
        vector_resize(vector, vector->capacity * 2);
    vector->value[vector->total] = c;
	// printf("vector_value: %s\n", vector->value);
	vector->total++;
}
 
// function that returns the value of an environment list node. give name of env_variable as argument
char	*get_environment_key_values(t_data *data, char	*input) // input = whole value of token from user from $ (could be USERP)
{
	t_env_list	*temp;
	int 		len;

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
	int start;
	char	*key;

	start = (*i);
	while (input[(*i)] && (ft_isalnum(input[(*i)]) || input[(*i)] == '_'))
		(*i)++;
	key = ft_substr(input, start, (*i) - start);
	if (key == NULL)
		exit_program("malloc", errno);
	return (key);
}

void	expand_env_variable(t_vector *vector, int *i, char *token_value, t_data *data)
{
	char	*env_key;
	char	*env_key_value;
	int j;
	
	(*i)++;
	if (token_value[*i] == '?')
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
		//GO TO FUNCTION expand_exit_code();
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
	env_key = get_environment_key(token_value, i);
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
		{
			expand_env_variable(vector, i, token_value, data);
		}
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
	{
		expand_single_quotes(vector, i, token_value);
	}
	if (token_value[*i] == '\"')
	{
		expand_double_quotes(vector, i, token_value, data);
	}
	if (token_value[*i] == '$')
	{
		expand_env_variable(vector, i, token_value, data);
	}
}

void	expand_token(char**	token_value, t_data *data)
{
	int i;
	t_vector vector;

    vector_init(&vector);
	i = 0;
	while ((*token_value)[i] != '\0')
	{
		if ((*token_value)[i] == '\'' || (*token_value)[i] == '\"' || (*token_value)[i] == '$')
		{
			expander(&vector, &i, *token_value, data);
		}
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

bool	check_dollar_sign(char	*str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return(true);
		i++;
	}
	return (false);
}

void expander_check(t_tokens *tokens_list, t_data *data)
{
	while (tokens_list != NULL)
	{
		if ((tokens_list->type == WORD) && (check_dollar_sign(tokens_list->value) == true))
			expand_token(&tokens_list->value, data);
		tokens_list = tokens_list->next;
	}
}



