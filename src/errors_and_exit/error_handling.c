#include "../../inc/minishell.h"

void	unexpected_token_error(t_data *data, t_tokens *token_list)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", STDERR_FILENO);
	ft_putstr_fd(token_list->value, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
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
