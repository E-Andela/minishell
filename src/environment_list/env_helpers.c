/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_helpers.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/04 18:28:31 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/22 12:30:53 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_element_back(t_env_list **list, t_env_list *new)
{
	t_env_list	*current;

	if (!*list)
	{
		*list = new;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new;
}

t_env_list	*ft_getenvp(char *key, t_env_list *list)
{
	int		len;

	len = 0;
	while (list)
	{
		len = ft_max(ft_strlen(key), ft_strlen(list->key));
		if (ft_strncmp(key, list->key, len) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	free_envp(t_env_list *head)
{
	t_env_list	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	swap_nodes(t_env_list *a, t_env_list *b)
{
	t_env_list	tmp;

	tmp.key = a->key;
	tmp.value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp.key;
	b->value = tmp.value;
}

t_env_list	*duplicate_node(t_env_list *node)
{
	t_env_list	*dup;

	dup = malloc(sizeof(t_env_list));
	if (!dup)
		shell_exit(MALLOC_FAIL);
	dup->key = ft_strdup(node->key);
	if (!dup->key)
		shell_exit(MALLOC_FAIL);
	if (node->value)
	{
		dup->value = ft_strdup(node->value);
		if (!dup->value)
			shell_exit(MALLOC_FAIL);
	}
	else
		dup->value = NULL;
	dup->next = NULL;
	return (dup);
}
