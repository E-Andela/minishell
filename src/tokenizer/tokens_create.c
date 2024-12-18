#include "../../inc/minishell.h"

// void	count_quotes(char *input, int *s, int *d)
// {
// 	int	i;

// 	*s = 0;
// 	*d = 0;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '\"')
// 			i += find_matching_quote(input, i, d, '\"');
// 		if (input[i] == '\'')
// 			i += find_matching_quote(input, i, s, '\'');
// 		i++;
// 	}
// }

t_tokens	*create_token_node(char *input, t_token_type token_type, int index, int quotes, t_data *data)
{
	t_tokens	*new_token;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new_token)
		exit_program(ERR_MALLOC, errno, data);
	new_token->value = ft_strdup(input);
	if (!new_token->value)
		exit_program(ERR_MALLOC, errno, data);
	new_token->type = token_type;
	new_token->index = index;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

t_tokens	*get_last_token(t_tokens *token_list)
{
	if (!token_list)
		return (NULL);
	while (token_list->next)
		token_list = token_list->next;
	return (token_list);
}




// int	find_matching_quote(char *input, int start, int *num_quotes, char quote)
// {
// 	int	i;

// 	i = start + 1;
// 	*num_quotes += 1;
// 	while (input[i] != '\0' && input[i] != quote)
// 		i++;
// 	if (input[i] == quote)
// 		*num_quotes += 1;
// 	return (i - start);
// }


void	add_token(char *input, t_token_type token_type, t_tokens **token_list, t_data *data)
{
	t_tokens	*new_token;
	t_tokens	*last_token;
	int			quotes;
	static int	index = 0;

	if (!(*token_list))
		index = 0;
	new_token = create_token_node(input, token_type, index++, quotes, data);
	if (!new_token)
		exit_program(ERR_MALLOC, errno, data);
	if (!(*token_list))
	{
		new_token->next = NULL;
		new_token->prev = NULL;
		*token_list = new_token;
	}
	else
	{
		last_token = get_last_token(*token_list);
		new_token->prev = last_token;
		last_token->next = new_token;
	}
}
