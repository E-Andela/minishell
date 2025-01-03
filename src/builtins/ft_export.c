/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/07 14:58:32 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/03 19:03:13 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_export_error(char *key, char *arg)
{
	if (key)
		free(key);
	error_not_a_valid_identifier(arg);
	return (1);
}

int	process_export_variable(char *arg, t_env_list *env_list)
{
	char		*key;
	char		*value;
	t_env_list	*new;

	key = get_key(arg);
	if (!valid_var_name(key) || !key)
		return (handle_export_error(key, arg));
	new = ft_getenvp(key, env_list);
	if (!new)
	{
		new = new_element(arg);
		add_element_back(&env_list, new);
	}
	else
	{
		value = get_value(arg);
		if (value)
		{
			free(new->value);
			new->value = value;
		}
	}
	free(key);
	return (0);
}

int	export_variables(char **args, t_env_list *env_list)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (args[i])
	{
		if (process_export_variable(args[i], env_list) == 1)
			status = 1;
		i++;
	}
	return (status);
}

int	print_export(t_env_list *list)
{
	t_env_list	*dup;
	t_env_list	*head;

	dup = dup_envp_list(list);
	head = dup;
	sort_envp_list(dup);
	while (dup)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(dup->key, STDOUT_FILENO);
		if (dup->value)
		{
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
			ft_putstr_fd(dup->value, STDOUT_FILENO);
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
	int	arg_count;
	int	status;

	arg_count = arg_counter(args);
	status = 0;
	if (arg_count == 1)
		status = print_export(env_list);
	else if (arg_count > 1)
		status = export_variables(args, env_list);
	return (status);
}
