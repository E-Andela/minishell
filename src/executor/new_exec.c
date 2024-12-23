#include "../../inc/minishell.h"

int execute_single_command(t_command *cmd_list, t_env_list *env_list)
{
	int status;
	int og_stdin;
	int og_stdout;

	og_stdin = dup(STDIN_FILENO);
	og_stdout = dup(STDOUT_FILENO);
	status = handle_redirections(cmd_list->redirections);
	dup2(og_stdin, STDIN_FILENO);
	dup2(og_stdout, STDOUT_FILENO);
	status = execute_builtin(cmd_list->args, env_list);
	return (status);
}

void execute_piped_commands(t_command *cmd_list, t_env_list *env_list)
{
	int **pipes;
	const int pipe_size = count_cmds(cmd_list) - 1;
	int id;
	char *path;

	if (pipe_size > 0)
	{
		pipes = create_pipes(pipe_size);
		if (!pipes)
			shell_exit(PIPE_FAIL);
	}
	while (cmd_list)
	{
		cmd_list->pid = fork();
		if (cmd_list->pid < 0)
			shell_exit(FORK_FAIL);
		init_child_signals();
		if (cmd_list->pid == 0)
		{
			handle_pipes(pipes, cmd_list, pipe_size);
			if (handle_redirections(cmd_list->redirections) != 0)
				exit(EXIT_FAILURE);
			if (is_builtin(cmd_list->args[0]))
				exit(execute_builtin(cmd_list->args, env_list));
			if (cmd_list->args)
			{
				path = get_path(cmd_list->args[0], ft_getenv("PATH", ft_ll2arr(env_list)));
				if (!path)
					shell_exit(CMD_FAIL);
				if (execve(path, cmd_list->args, ft_ll2arr(env_list)) == -1)
					shell_exit(EXECVE_FAIL);
			}
		}
		cmd_list = cmd_list->next;		
	}
	close_pipes(pipes, pipe_size);
}

int execute_commands(t_command *cmd_list, t_env_list *env_list)
{
	int status;

	status = 0;
	status = create_heredocs(cmd_list);
	if (status != 0)
		return (status);
	if (count_cmds(cmd_list) == 1 && is_builtin(cmd_list->args[0]))
		status = execute_single_command(cmd_list, env_list);
	else
	{
		execute_piped_commands(cmd_list, env_list);
		status = wait_for_children(cmd_list);
	}
	return (status);
}

// int main()
// {
// 	is_builtin(NULL);
// }