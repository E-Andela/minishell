#include "../../inc/minishell.h"

int execute_single_command(t_command *cmd_list, t_env_list *env_list)
{
	int status;

	status = handle_redirections(cmd_list->redirections);
	status = execute_builtin(cmd_list->args, env_list);
	return (status);
}

int execute_piped_commands(t_command *cmd_list, t_env_list *env_list)
{
	int **pipes;
	const int pipe_size = count_cmds(cmd_list) - 1;
	int status;
	int id;
	char *path;

	status = 0;
	pipes = create_pipes(pipe_size);
	while (cmd_list)
	{
		id = fork();
		if (id == 0)
		{
			handle_pipes(pipes, cmd_list, pipe_size);
			if (handle_redirections(cmd_list->redirections) != 0)
				return (1);
			if (is_builtin(cmd_list->args[0]))
			{
				status = execute_builtin(cmd_list->args, env_list);
				exit(status);
			}
			if (cmd_list->args)
			{
				path = get_path(cmd_list->args[0], ft_getenv("PATH", ft_ll2arr(env_list)));
				if (!path)
				{
					perror("command not found");
					exit(1);
				}
				if (execve(path, cmd_list->args, ft_ll2arr(env_list)) == -1)
				{
					perror("execve failed");
					exit(1);
				}
			}
		}
		cmd_list = cmd_list->next;		
	}
	close_pipes(pipes, pipe_size);
	return (status);
}

int execute_commands(t_command *cmd_list, t_env_list *env_list)
{
	int status;

	status = 0;
	if (count_cmds(cmd_list) == 1 && is_builtin(cmd_list->args[0]))
		status = execute_single_command(cmd_list, env_list);
	else
		status = execute_piped_commands(cmd_list, env_list);
	return (status);
}

// int main()
// {
// 	is_builtin(NULL);
// }