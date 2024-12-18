#include "../inc/minishell.h"

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

	while (1)
	{
		input = readline(USER_MSG);
		if (!input)
			continue ;
		data->user_input = ft_strtrim(input, " ");
		if (!data->user_input)
			exit_program(ERR_MALLOC, errno, data);
		if (data->user_input[0] == '\0')
			continue ;
		add_history(input);
		free(input);

		tokenizer(data->user_input, data);
		print_tokens(data->tokens_list);

		expander_check(data->tokens_list, data);
		printf("after expantion:\n");
		print_tokens(data->tokens_list);


		parser(data);
		printf("after parser:\n");
		print_cmd_list(data->command_list);

		set_index(data->command_list);
		execute_commands(data->command_list, data->environment);
		wait_for_children();
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argv;
	if (argc != 1)
		exit_program(ERR_ARGC, errno, data);
	data = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (data == NULL)
		exit(EXIT_FAILURE);
	data->environment = ft_arr2ll(envp);
	mini_loop(data);
	free_data(data);
	return (0);
}
