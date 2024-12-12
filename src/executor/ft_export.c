/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/07 14:58:32 by eandela       #+#    #+#                 */
/*   Updated: 2024/12/12 17:41:21 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int arg_counter(char **args)
{
	int	count;

	count = 0;
	while (args[count])
	{
		// printf("%s\n", args[count]);
		count++;
	}
	return (count);
}

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

char *get_key(char *key_value)
{
	int		eq;
	char	*key;
	
	eq = get_eq_index(key_value);
	if (eq < 0)
	{
		// printf("eq: %i\n", eq);
		key = ft_strdup(key_value);
		if (!key)
			return (NULL);
		return (key);
	}
	key = malloc(sizeof(char) * (eq + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, key_value, eq + 1);
	return (key);
}

char *get_value(char *key_value)
{
	int		eq;
	char	*value;

	eq = get_eq_index(key_value);
	if (eq < 0)
		return (NULL);
	value = ft_strdup(key_value + eq + 1);
	if (!value)
		return (NULL);
	return (value);
}

/**
 * export_variables - Exports environment variables.
 * @args: An array of strings representing the arguments.
 * @env_list: A pointer to the linked list of environment variables.
 *
 * This function iterates through the provided arguments and exports
 * them as environment variables. For each argument, it extracts the
 * key and value, validates the key, and either updates an existing
 * environment variable or adds a new one to the list. If the key is
 * invalid, the function sets the exit status to 1. The function
 * returns the exit status, which is 0 if all variables were exported
 * successfully, or 1 if there were any invalid keys.
 *
 * Return: 0 if all variables were exported successfully, 1 if there
 *         were any invalid keys.
 */
int export_variables(char **args, t_env_list *env_list)
{
	int 	exit_status;
	int		i;
	t_env_list	*new;
	char	*key;
	char	*value;
	
	exit_status = 0;
	i = 1;
	while (args[i])
	{
		key = get_key(args[i]);
		if (valid_var_name(key))
		{
			new = ft_getenvp(key, env_list);
			if (!new)
			{
				new = new_element(args[i]);
				if (!new)
					return (1);
				add_element_back(&env_list, new);
			}
			else
			{
				value = get_value(args[i]);
				if (value)
				{
					free(new->key_value);
					new->key_value = value;
				}
			}			
		}
		else
		{
			perror("export: not a valid identifier");
			exit_status = 1;
		}
		free(key);
		i++;
	}
	return (exit_status);	
}

void	sort_envp_list(t_env_list *head)
{
	t_env_list *current;
	t_env_list *compare;

	if (head == NULL || head->next == NULL)
        return;

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
	t_env_list *dup;
	t_env_list *tmp;
	
	dup = NULL;
	while (head)
	{
		tmp = duplicate_node(head);
		add_element_back(&dup, tmp);
		head = head->next;
	}
	return (dup);
}

int	print_export(t_env_list *list)
{
	t_env_list *dup;
	t_env_list *head;
	
	dup = dup_envp_list(list);
	head = dup;
	sort_envp_list(dup);
	while (dup)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(dup->key, STDOUT_FILENO);
		if (dup->key_value)
		{
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
			ft_putstr_fd(dup->key_value, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		dup = dup->next;
	}
	free_envp(head);
	return (0);
}

int	ft_export(char **args, t_env_list *env_list)
{
	int arg_count;
	int	status;

	arg_count = arg_counter(args);
	status = 0;
	if (arg_count == 1)
		status = print_export(env_list);
	else if (arg_count > 1)
		status = export_variables(args, env_list);
	return (status);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env_list *list;
// 	// t_envp *copy;
	
// 	char *args[] = {"export", "hi=yes", "hello", "hi=no", "whatsup=", NULL};
// 	char *args2[] = {"export", NULL};
	
// 	list = ft_arr2ll(envp);
// 	ft_export(args, list);
// 	ft_export(args2, list);
// 	// print_ll(list);
// 	// printf("\n\n\n");
// 	// copy = dup_envp_list(list);
// 	// sort_envp_list(copy);
// 	// print_ll(copy);
// 	// printf("\n\n\n");
// 	// print_ll(list);
// 	// free_envp(list);
// 	// free_envp(copy);
// 	free_envp(list);
// 	if (!argc || !argv || !envp)
// 		return (0);
// }