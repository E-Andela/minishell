#include "../../inc/minishell.h"

void	free_data(t_data *data)
{
	if (data->user_input)
		free(data->user_input);
	if (data->environment)
	{
		free_env_list(data->environment);
		data->environment = NULL;
	}
	if (data->tokens_list)
	{
		free_tokens_list(data->tokens_list);
		data->tokens_list = NULL;
	}
	if (data->command_list)
	{
		free_command_list(data->command_list);
		data->command_list = NULL;
	}
	free(data);
}

void	reset_data(t_data *data)
{
	if (data->user_input)
		free(data->user_input);
	if (data->tokens_list)
	{
		free_tokens_list(data->tokens_list);
		data->tokens_list = NULL;
	}
	if (data->command_list)
	{
		free_command_list(data->command_list);
		data->command_list = NULL;
	}
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

void	shell_exit(t_error_type error)
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
	if (error == EXECVE_FAIL)
		perror("Execve failed");
	exit(errno);
}
