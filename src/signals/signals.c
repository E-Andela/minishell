# include "../../inc/minishell.h"

int event()
{
	return (0);
}

void sigint_handler(int signal)
{
	g_signal = signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler_child(int signal)
{
	g_signal = signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void sigint_handler_heredoc(int signal)
{
	g_signal = signal;
	rl_done = 1;
}

void	quit(int signal)
{
	g_signal = signal;
	printf("Quit (core dumped)\n");
}
void init_signals()
{
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_child_signals()
{
	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, quit);
}

void init_heredoc_signals()
{
	signal(SIGINT, sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}