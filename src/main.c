/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 14:36:09 by livliege      #+#    #+#                 */
/*   Updated: 2024/10/10 15:10:07 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	reset_data(t_data *data)
{
	// if (data->tokens_list)
	// {
	// 	free_tokens(data->tokens_list);
	// 	data->tokens_list = NULL;
	// }
	// if (data->user_input)
	// {
	// 	free(data->user_input);
	// 	data->user_input = NULL;
	// }
	free_tokens(data->tokens_list);
	data->tokens_list = NULL;
	free(data->user_input);
	mini_loop(data);
}

void set_index(t_command *cmd_list)
{
	int i = 0;
	while (cmd_list)
	{
		cmd_list->index	= i;
		cmd_list = cmd_list->next;
		i++;
	}
}

void mini_loop(t_data *data)
{
	char	*input;

	// printf("%s", RED);
	input = readline(USER_MSG);
	// printf("%s", DEFAULT);

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
	
	// handle words -> we need to check which token type each node with text is
	

	// expander(data->tokens_list);
	// go to parser function


	// go to execution function aka elroy's code



	// printf("\ntoken list after tokenizer: \n\n");
	// print_tokens(data->tokens_list);

	expander_check(data->tokens_list, data);
	
	// printf("\ntoken list after expention: \n\n");
	// print_tokens(data->tokens_list);
	
	parser(data);
	set_index(data->command_list);
	execute_commands(data->command_list, data->environment);
	wait_for_children();
	
	// printf("\nCommands list after parser: \n\n");
    // print_cmd_list(data->command_list);

	reset_data(data);
}

int main(int argc, char **argv, char **envp)
{
	(void) argv;
	t_data	*data;
	
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


