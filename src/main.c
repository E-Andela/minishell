#include "../inc/minishell.h"

int g_signal = 0;



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
		{
			// free_data(data);
			shell_exit(EXIT);
		}
		if (g_signal == SIGINT)
			data->exit_code = 130;
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
		{
			printf("%sPARSER ERROR!%s\n", RED, DEFAULT);
			continue ;
		}

		// printf("after parser:\n");
		// print_cmd_list(data->command_list);

		// if (!syntax_checker(data))
		// {
		// 	printf("%sSYNTAX ERROR!%s\n", RED, DEFAULT);
		// 	continue;
		// }

		data->exit_code = execute_commands(data->command_list, data->environment);
		if (data->exit_code == -1)
		{
			free_data(data);
			exit (127);
		}
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
