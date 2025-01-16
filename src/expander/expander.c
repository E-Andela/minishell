/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:13:02 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/16 15:13:02 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_vector	*expand_exit_code(t_vector *vector, t_data *data)
{
	char	*exit_code;
	int		i;

	exit_code = ft_itoa(data->exit_code);
	if (!exit_code)
		exit_program(ERR_MALLOC, data);
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
	
	// printf("%stoken_value:%s\n%s", BLUE, *token_value, DEFAULT);		// TAKE OUT!!!!!!!!!!!
	// printf("%svector_value:%s\n%s", BLUE, vector.value, DEFAULT);		// TAKE OUT!!!!!!!!!!!
	
	if (ft_strlen(vector.value) == 0)
	{
		// printf("%sTEST\n%s", RED, DEFAULT);		// TAKE OUT!!!!!!!!!!!
		if (token_node->prev && is_redirect(token_node->prev->type))
		{
			error_ambiguous_redirect(token_node);
			free(vector.value);
			return (false);
		}
		if (!ft_strchr(*token_value, '\"'))
		{
			free(vector.value);
			return (false);
		}
	}
	// printf("%sTEST\n%s", GREEN, DEFAULT);		// TAKE OUT!!!!!!!!!!!
	free(*token_value);
	*token_value = ft_strdup(vector.value);
	if (*token_value == NULL)
		exit_program(ERR_MALLOC, data);
	free(vector.value);
	return (true);
}
