/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/04 23:13:24 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/23 10:41:31 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_single_command(t_command *cmd_list, t_env_list **env_list)
{
	int	status;
	int	og_stdin;
	int	og_stdout;

	og_stdin = dup(STDIN_FILENO);
	og_stdout = dup(STDOUT_FILENO);
	status = handle_redirections(cmd_list->redirections);
	status = execute_builtin(cmd_list->args, env_list);
	dup2(og_stdin, STDIN_FILENO);
	dup2(og_stdout, STDOUT_FILENO);
	return (status);
}

void	execute_child_process(t_command *cmd_list, int **pipes, \
int pipe_size, t_env_list **env_list)
{
	char	*path;

	handle_pipes(pipes, cmd_list, pipe_size);
	if (handle_redirections(cmd_list->redirections) != 0)
		exit(EXIT_FAILURE);
	if (cmd_list->args)
	{
		if (is_builtin(cmd_list))
			exit(execute_builtin(cmd_list->args, env_list));
		path = get_path(cmd_list->args[0], get_envp_value("PATH", *env_list));
		check_if_directory(path, cmd_list);
		if (execve(path, cmd_list->args, ft_ll2arr(*env_list)) == -1)
			shell_exit(EXECVE_FAIL);
	}
	else
		exit(EXIT_SUCCESS);
}

void	fork_and_execute(
	t_command *cmd_list,
	int **pipes,
	int pipe_size,
	t_env_list **env_list
)
{
	cmd_list->pid = fork();
	if (cmd_list->pid < 0)
		shell_exit(FORK_FAIL);
	init_child_signals();
	if (cmd_list->pid == 0)
		execute_child_process(cmd_list, pipes, pipe_size, env_list);
}

int	execute_piped_commands(t_command *cmd_list, t_env_list **env_list)
{
	int			**pipes;
	const int	pipe_size = count_cmds(cmd_list) - 1;

	if (pipe_size > 0)
	{
		pipes = create_pipes(pipe_size);
		if (!pipes)
			shell_exit(PIPE_FAIL);
	}
	while (cmd_list)
	{
		fork_and_execute(cmd_list, pipes, pipe_size, env_list);
		cmd_list = cmd_list->next;
	}
	close_pipes(pipes, pipe_size);
	return (0);
}

int	execute_commands(t_command *cmd_list, t_env_list **env_list)
{
	int	status;

	status = 0;
	status = create_heredocs(cmd_list);
	if (status != 0)
		return (status);
	if (count_cmds(cmd_list) == 1 && is_builtin(cmd_list))
		status = execute_single_command(cmd_list, env_list);
	else
	{
		if (execute_piped_commands(cmd_list, env_list) == -1)
			return (-1);
		status = wait_for_children(cmd_list);
	}
	return (status);
}
