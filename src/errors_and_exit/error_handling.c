#include "../../inc/minishell.h"

void	error_unexpected_token(t_tokens *token_list)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(token_list->value, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	error_ambiguous_redirect(t_tokens *token_list)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(token_list->value, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
}

void	error_command_not_found(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("command not found\n", STDERR_FILENO);
	exit(127);
}

void	error_not_a_valid_identifier(char** identifier)
{
	int	j;

	j = 0;
	while (identifier[j + 1] != NULL)
		j++;
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(identifier[j], STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void display_error(char *error_msg)
{
	perror(error_msg);
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
	// if (error == CMD_FAIL)
	// {
	// 	ft_putstr_fd("command: \n", STDERR_FILENO);
	// 	ft_putstr_fd("command not found\n", STDERR_FILENO);
	// 	exit(127);
	// }
	if (error == EXECVE_FAIL)
		perror("Execve failed");
	exit(errno);
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
