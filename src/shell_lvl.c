/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_lvl.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 14:56:19 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/16 15:06:28 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	increase_shlvl(t_env_list	*env_list)
{
	t_env_list	*shell_lvl;
	int			lvl;

	shell_lvl = ft_getenvp("SHLVL", env_list);
	if (!shell_lvl)
		return ;
	lvl = ft_atoi(shell_lvl->value);
	lvl++;
	free(shell_lvl->value);
	shell_lvl->value = ft_itoa(lvl);
}
