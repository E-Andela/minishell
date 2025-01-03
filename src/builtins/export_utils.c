/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/03 18:33:12 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/03 18:34:46 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	valid_var_name(char	*name)
{
	int	i;

	i = 0;
	if (!name || !name[i])
		return (0);
	while (name[i])
	{
		if (i == 0)
			if (!ft_isalpha(name[i]) && name[i] != '_')
				return (0);
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*get_key(char *key_value)
{
	int		eq;
	char	*key;

	eq = get_eq_index(key_value);
	if (eq < 0)
	{
		key = ft_strdup(key_value);
		if (!key)
			return (NULL);
		return (key);
	}
	key = malloc(sizeof(char) * (eq + 1));
	if (!key)
		shell_exit(MALLOC_FAIL);
	ft_strlcpy(key, key_value, eq + 1);
	return (key);
}

char	*get_value(char *key_value)
{
	int		eq;
	char	*value;

	eq = get_eq_index(key_value);
	if (eq < 0)
		return (NULL);
	value = ft_strdup(key_value + eq + 1);
	if (!value)
		shell_exit(MALLOC_FAIL);
	return (value);
}

void	sort_envp_list(t_env_list *head)
{
	t_env_list	*current;
	t_env_list	*compare;

	if (head == NULL || head->next == NULL)
		return ;
	current = head;
	while (current)
	{
		compare = current->next;
		while (compare)
		{
			if (ft_strncmp(current->key, compare->key, __SIZE_MAX__) > 0)
				swap_nodes(current, compare);
			compare = compare->next;
		}
		current = current->next;
	}
}

t_env_list	*dup_envp_list(t_env_list *head)
{
	t_env_list	*dup;
	t_env_list	*tmp;

	dup = NULL;
	while (head)
	{
		tmp = duplicate_node(head);
		add_element_back(&dup, tmp);
		head = head->next;
	}
	return (dup);
}
