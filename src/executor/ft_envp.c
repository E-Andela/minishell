/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_envp.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/04 18:28:31 by eandela       #+#    #+#                 */
/*   Updated: 2024/12/19 22:23:59 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*key_val_to_str(t_env_list *element)
{
	int		len;
	char	*string;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	len = ft_strlen(element->key) + ft_strlen(element->key_value) + 2;
	string = malloc(sizeof(char) * len);
	if (!string)
		shell_exit(MALLOC_FAIL);
	string[len - 1] = '\0';
	while (i < len)
	{
		if (i < (int)ft_strlen(element->key))
			string[i] = element->key[i];
		else if (i == (int)ft_strlen(element->key))
			string[i] = '=';
		else 
		{
			string[i] = element->key_value[j];
			j++;
		}
		i++;
	}
	return (string);
}

int	ll_count(t_env_list *list, bool skip_null)
{
	int	i;

	i = 0;
	while (list)
	{
		if (skip_null)
		{
			if (list->key != NULL && list->key_value != NULL)
				i++;
		}
		else
			i++;
		list = list->next;
	}
	return (i);
}

char **ft_ll2arr(t_env_list *envp)
{
	char **ret;
	int	entries;
	int i;

	i = 0;
	entries = ll_count(envp, true);
	ret = malloc(sizeof(char*) * (entries + 1));
	if (!ret)
		shell_exit(MALLOC_FAIL);
	ret[entries] = NULL;
	while (envp)
	{
		if (envp->key_value)
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

t_env_list *new_element(char *envp)
{
	t_env_list *element;
	int	i;
	
	i = get_eq_index(envp);
	element = malloc(sizeof(t_env_list));
	if (!element)
		shell_exit(MALLOC_FAIL);
	if (i < 0)
	{
		element->key = ft_strdup(envp);
		element->key_value = NULL;
		element->next = NULL;
		return (element);
	}
	element->key = ft_substr(envp, 0, i);
	if (!element->key)
		shell_exit(MALLOC_FAIL);
	element->key_value = ft_strdup(envp + (i + 1));
	if (!element->key_value)
		shell_exit(MALLOC_FAIL);
	element->next = NULL;
	return (element);
}

void add_element_back(t_env_list **list, t_env_list *new)
{
	t_env_list *current;
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

t_env_list	*ft_arr2ll(char **envp)
{
	t_env_list	*head;
	t_env_list	*tmp;
	t_env_list	*cur;
	int	i;

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

void	print_ll(t_env_list	*list)
{
	while (list)
	{
		printf("key: %s, value: %s\n", list->key, list->key_value);
		list = list->next;
	}
}

void	print_str_array(char **str_arr)
{
	int i;
	i = 0;
	while (str_arr[i])
	{
		printf("%s\n", str_arr[i]);
		i++;
	}
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

t_env_list *ft_getenvp(char *key, t_env_list *list)
{
	int		i;
	int		len;
	
	i = 0;
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
	t_env_list *tmp;
	
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->key_value)
			free(tmp->key_value);
		free(tmp);
	}
}

void	swap_nodes(t_env_list *a, t_env_list *b)
{
	t_env_list	tmp;
	
	tmp.key = a->key;
	tmp.key_value = a->key_value;
	a->key = b->key;
	a->key_value = b->key_value;
	b->key = tmp.key;
	b->key_value = tmp.key_value;	
}

t_env_list *duplicate_node(t_env_list *node)
{
	t_env_list *dup;

	dup = malloc(sizeof(t_env_list));
	if (!dup)
		shell_exit(MALLOC_FAIL);
	dup->key = ft_strdup(node->key);
	if (!dup->key)
		shell_exit(MALLOC_FAIL);
	if (node->key_value)
	{
		dup->key_value = ft_strdup(node->key_value);
		if (!dup->key_value)
			shell_exit(MALLOC_FAIL);
	}
	dup->next = NULL;
	return (dup);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_envp *list;
// 	t_envp *new;

// 	list = new_element("hello");
// 	new = new_element("world");
// 	add_element_back(list, new);
	
// 	print_ll(list);
// 	if (!argc || !argv || !envp)
// 		return (0);
	
// }