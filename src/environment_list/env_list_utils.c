/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/05 22:46:41 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/05 22:56:55 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ll_count(t_env_list *list, bool skip_null)
{
	int	i;

	i = 0;
	while (list)
	{
		if (skip_null)
		{
			if (list->key != NULL && list->value != NULL)
				i++;
		}
		else
			i++;
		list = list->next;
	}
	return (i);
}

int	get_eq_index(char *element)
{
	int	i;

	i = 0;
	while (element[i])
	{
		if (element[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
