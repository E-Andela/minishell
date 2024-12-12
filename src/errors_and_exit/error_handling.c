/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 14:42:47 by livliege      #+#    #+#                 */
/*   Updated: 2024/12/12 14:42:47 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	unexpected_token_error(t_data *data, t_tokens *token_list)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", STDERR_FILENO);
    ft_putstr_fd(token_list->value, STDERR_FILENO);
    ft_putstr_fd("'\n", STDERR_FILENO);
	reset_data(data);
	return (EXIT_FAILURE);
}
