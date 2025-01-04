/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_init.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/04 19:40:47 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/04 19:41:24 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	event(void)
{
	return (0);
}

void	init_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_child_signals(void)
{
	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, quit);
}

void	init_heredoc_signals(void)
{
	signal(SIGINT, sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
