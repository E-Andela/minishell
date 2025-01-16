/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 16:04:19 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/16 16:04:19 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_unexpected_token(t_tokens *token_list)
{
	ft_putstr_fd("minishell: syntax error near \
unexpected token `", STDERR_FILENO);
	ft_putstr_fd(token_list->value, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	error_ambiguous_redirect(t_tokens *token_list)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(token_list->value, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
}

int	error_command_not_found(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("command not found\n", STDERR_FILENO);
	return (127);
}

void	error_not_a_valid_identifier(char *identifier)
{
	int	j;

	j = 0;
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	display_error(char *error_msg)
{
	perror(error_msg);
}
