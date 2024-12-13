#include "../inc/minishell.h"

void	reset_data(t_data *data)
{
	free_tokens(data->tokens_list);
	data->tokens_list = NULL;
	free(data->user_input);
	mini_loop(data);
}

void	set_index(t_command *cmd_list)
{
	int	i;

	i = 0;
	while (cmd_list)
	{
		cmd_list->index = i;
		cmd_list = cmd_list->next;
		i++;
	}
}

void	mini_loop(t_data *data)
{
	char	*input;

	input = readline(USER_MSG);
	data->user_input = ft_strtrim(input, " ");
	if (data->user_input[0] == '\0')
	{
		ft_putendl_fd("exiting minishell...\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	add_history(input);
	free(input);
	if (!check_for_quotes(data->user_input))
		return (exit_program(ERR_QUOTES, errno));
	if (!tokenizer(data->user_input, data))
		return (exit_program(ERR_TOKEN, errno));
	expander_check(data->tokens_list, data);
	parser(data);
	set_index(data->command_list);
	execute_commands(data->command_list, data->environment);
	wait_for_children();
	reset_data(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argv;
	if (argc != 1)
		exit_program(ERR_ARGC, errno);
	data = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (data == NULL)
		exit(EXIT_FAILURE);
	// parse_env(envp, data);
	data->environment = ft_arr2ll(envp);
	// expander_loop(data);
	mini_loop(data);
	free_everything(data);
	return (0);
}
