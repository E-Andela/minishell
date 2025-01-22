/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/05 22:43:16 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/22 12:31:23 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*key_val_to_str(t_env_list *element)
{
	int		len;
	char	*string;

	len = ft_strlen(element->key) + ft_strlen(element->value) + 2;
	string = malloc(sizeof(char) * len);
	if (!string)
		shell_exit(MALLOC_FAIL);
	string[len - 1] = '\0';
	ft_strlcpy(string, element->key, len);
	ft_strlcat(string, "=", len);
	ft_strlcat(string, element->value, len);
	return (string);
}

t_env_list	*new_element(char *envp)
{
	t_env_list	*element;
	int			i;

	i = get_eq_index(envp);
	element = malloc(sizeof(t_env_list));
	if (!element)
		shell_exit(MALLOC_FAIL);
	if (i < 0)
	{
		element->key = ft_strdup(envp);
		element->value = NULL;
		element->next = NULL;
		return (element);
	}
	element->key = ft_substr(envp, 0, i);
	if (!element->key)
		shell_exit(MALLOC_FAIL);
	element->value = ft_strdup(envp + (i + 1));
	if (!element->value)
		shell_exit(MALLOC_FAIL);
	element->next = NULL;
	return (element);
}

t_env_list	*ft_arr2ll(char **envp)
{
	t_env_list	*head;
	t_env_list	*tmp;
	t_env_list	*cur;
	int			i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		tmp = new_element(envp[i]);
		if (!head)
		{
			head = tmp;
			cur = head;
		}
		else
		{
			cur->next = tmp;
			cur = cur->next;
		}
		i++;
	}
	return (head);
}

char	**ft_ll2arr(t_env_list *envp)
{
	char	**ret;
	int		entries;
	int		i;

	i = 0;
	entries = ll_count(envp, true);
	ret = malloc(sizeof(char *) * (entries + 1));
	if (!ret)
		shell_exit(MALLOC_FAIL);
	ret[entries] = NULL;
	while (envp)
	{
		if (envp->value)
		{
			ret[i] = key_val_to_str(envp);
			if (!ret[i])
			{
				ft_free_dbl(ret);
				return (NULL);
			}
			i++;
		}
		envp = envp->next;
	}
	return (ret);
}

char	*get_envp_value(char *key, t_env_list *env_list)
{
	t_env_list	*node;

	node = ft_getenvp(key, env_list);
	if (!node)
		return (NULL);
	return (node->value);
}
