#include "../../inc/minishell.h"

void	unexpected_token_error(t_data *data, t_tokens *token_list)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", STDERR_FILENO);
	ft_putstr_fd(token_list->value, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void shell_exit(t_error_type error)
{
	if (error == ARGUMENTS_FAIL)
		ft_putstr_fd("Please execute without arguments\n", STDERR_FILENO);
	if (error == MALLOC_FAIL)
		perror("Malloc failed");
	if (error == PIPE_FAIL)
		perror("Pipe failed");
	if (error == FORK_FAIL)
		perror("Fork failed");
	if (error == EXIT)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (error == OPEN_FAIL)
		perror("Open failed");
	if (error == CWD_FAIL)
		perror("Unknown error occured");
	if (error == CMD_FAIL)
	{
		ft_putstr_fd("Command not found\n", STDERR_FILENO);
		exit(127);
	}
	if (error == EXECVE_FAIL)
		perror("Execve failed");
	exit(errno);
}

void display_error(char *error_msg)
{
	perror(error_msg);
}

void	exit_program(char *error_message, int errnbr, t_data *data)
{
	free_data(data);
	if (errnbr == 127)
		write(STDERR_FILENO, error_message, ft_strlen(error_message));
	else
		perror(error_message);
	exit(errnbr);
}
