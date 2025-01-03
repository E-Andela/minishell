/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/18 19:25:20 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/02 21:17:27 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_list	*prev_node(t_env_list *node, t_env_list *list)
{
	t_env_list	*prev;

	prev = NULL;
	while (list)
	{
		if (list == node)
			return (prev);
		prev = list;
		list = list->next;
	}
	return (NULL);
}

int	ft_unset(char **args, t_env_list **env_list)
{
	int			i;
	t_env_list	*prev;
	t_env_list	*cur;
	t_env_list	*next;

	i = 1;
	while (args[i])
	{
		cur = ft_getenvp(args[i], *env_list);
		i++;
		if (!cur)
			continue ;
		prev = prev_node(cur, *env_list);
		next = cur->next;
		if (cur->key)
			free(cur->key);
		if (cur->value)
			free(cur->value);
		free(cur);
		if (!prev)
			*env_list = next;
		else
			prev->next = next;
	}
	return (0);
}
