/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 15:14:10 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/16 15:14:10 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	run_tester(t_data *data)
{
	char	*input;

	input = get_next_line(STDIN_FILENO);
	if (input && *input)
	{
		data->user_input = ft_strtrim(input, " \t\v\f\r\n");
		if (!data->user_input)
			exit_program(ERR_MALLOC, data);
		process_input(data);
		if (data->exit_code)
			return (data->exit_code);
		add_history(input);
		execute_and_handle_exit(data);
		free(input);
	}
	return (data->exit_code);
}
