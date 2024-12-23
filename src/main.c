#include "../inc/minishell.h"

int g_signal = 0;

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
	
	data->exit_code = 0;
	while (1)
	{
		g_signal = 0;
    reset_data(data);

		init_signals();
		input = readline(USER_MSG);
		if (!input)
			shell_exit(EXIT);
		data->user_input = ft_strtrim(input, " ");
		if (!data->user_input)
			shell_exit(MALLOC_FAIL);
		if (data->user_input[0] == '\0')
			continue ;
		add_history(input);
		free(input);

		tokenizer(data->user_input, data);
		// print_tokens(data->tokens_list);

		expander_check(data->tokens_list, data);
		// printf("after expantion:\n");
		// print_tokens(data->tokens_list);
		
		if (!parser(data))
			continue ;

		// printf("after parser:\n");
		// print_cmd_list(data->command_list);

		set_index(data->command_list);
		data->exit_code = execute_commands(data->command_list, data->environment);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	// (void) argv;
	if (argc != 1)
		shell_exit(ARGUMENTS_FAIL);
	data = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (data == NULL)
		shell_exit(MALLOC_FAIL);
	data->environment = ft_arr2ll(envp);
	mini_loop(data);
	free_data(data);
	return (0);
}
