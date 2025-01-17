/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:14:10 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/16 15:14:10 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal = 0;

void	execute_and_handle_exit(t_data *data)
{
	data->exit_code = execute_commands(data->command_list, data->environment);
	if (data->exit_code == -1)
	{
		free_data(data);
		exit(127);
	}
}

bool	process_input(t_data *data)
{
	tokenizer(data->user_input, data);
	if (!expander_check(data->tokens_list, data))
		return (false);
	if (!parser(data))
		return (false);
	return (true);
}

bool	handle_input(t_data *data)
{
	char	*input;

	g_signal = 0;
	init_signals();
	input = readline(USER_MSG);
	if (!input)
	{
		free(input);
		shell_exit(EXIT);
	}
	if (g_signal == SIGINT)
		data->exit_code = 130;
	data->user_input = ft_strtrim(input, " \t\v\f\r\n");
	if (!data->user_input)
		exit_program(ERR_MALLOC, data);
	if (data->user_input[0] == '\0')
	{
		free(input);
		return (false);
	}
	add_history(input);
	free(input);
	return (true);
}

void	mini_loop(t_data *data)
{
	data->exit_code = 0;
	while (1)
	{
		reset_data(data);
		if (!handle_input(data))
			continue ;
		if (!process_input(data))
			continue ;
		execute_and_handle_exit(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_env_list	*env_list;

	if (argc != 1)
		shell_exit(ARGUMENTS_FAIL);
	(void) argv;
	data = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (data == NULL)
		exit_program(ERR_MALLOC, data);
	env_list = ft_arr2ll(envp);
	data->environment = &env_list;
	increase_shlvl(*data->environment);
	mini_loop(data);
	free_data(data);
	return (0);
}
