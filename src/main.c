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
			shell_exit(EXIT);
		data->user_input = ft_strtrim(input, " ");
		if (!data->user_input)
			shell_exit(MALLOC_FAIL);
		if (data->user_input[0] == '\0')
			continue ;
		add_history(input);
		free(input);

		tokenizer(data->user_input, data);
		
		printf("tokens:\n");				//TAKE OUT
		print_tokens(data->tokens_list);			//TAKE OUT

		if (!expander_check(data->tokens_list, data))
		{
			continue ;
		}
		printf("after expantion:\n");				//TAKE OUT
		print_tokens(data->tokens_list);			//TAKE OUT
		
		if (!parser(data))
		{
			continue ;
		}

		printf("after parser:\n");					//TAKE OUT
		print_cmd_list(data->command_list);			//TAKE OUT
		printf("%s----------------------------------%s\n", BLUE, DEFAULT);			//TAKE OUT

		data->exit_code = execute_commands(data->command_list, data->environment);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 1)
		shell_exit(ARGUMENTS_FAIL);
	(void) argv;
	data = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (data == NULL)
		shell_exit(MALLOC_FAIL);
	data->environment = ft_arr2ll(envp);
	mini_loop(data);
	free_data(data);
	return (0);
}
