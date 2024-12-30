#include "../../inc/minishell.h"

char	*get_env_name(char *input)
{
	char	*name;
	int		i;

	i = 0;
	while (input[i] != '=' && input[i] != '\0')
		i++;
	name = ft_substr(input, 0, i);
	return (name);
}

char	*get_env_value(char *input)
{
	char	*value;

	value = ft_strchr(input, '=');
	if (value != NULL)
		value++;
	return (value);
}

t_env_list	*create_linked_list_node(char *input)
{
	t_env_list	*new_node;

	new_node = (t_env_list *)malloc(sizeof(t_env_list));
	if (new_node == NULL)
		return (NULL);
	new_node->key = get_env_name(input);
	new_node->value = get_env_value(input);
	new_node->next = NULL;
	return (new_node);
}

// add node to back of the list
void	env_create_linked_list(char *input, t_env_list **environment)
{
	t_env_list	*new_node;
	t_env_list	*last_node;

	new_node = create_linked_list_node(input);
	if (new_node == NULL)
		exit(EXIT_FAILURE);
	if (!*environment)
		*environment = new_node;
	else
	{
		last_node = *environment;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

void	parse_env(char **envp, t_data *data)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		env_create_linked_list(envp[i], &data->environment);
		i++;
	}
}
