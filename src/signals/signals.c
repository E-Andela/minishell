# include "../../inc/minishell.h"

void sigint_handler(int signal)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler_child(int signal)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	quit(int signal)
{
	printf("Quit (core dumped)\n");
}
void init_signals()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_child_signals()
{
	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, quit);
}