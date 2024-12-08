/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:34:14 by marvin            #+#    #+#             */
/*   Updated: 2024/11/27 12:34:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
	
    // UNSET,
	// CMD,
	// WORD,
	// SINGLE_QUOTED,   '
	// DOUBLE_QUOTED,   "
	// PIPE,            |
	// OUT_APPEND,      >>
	// OUT_REDIRECT,    >
	// IN_REDIRECT,     <
	// HERE_DOC         <<

#include "../inc/minishell.h"

int	unexpected_token_error(t_data *data, t_tokens *token_list)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", STDERR_FILENO);
    ft_putstr_fd(token_list->value, STDERR_FILENO);
    ft_putstr_fd("'\n", STDERR_FILENO);
	reset_data(data);
	return (EXIT_FAILURE);
}
