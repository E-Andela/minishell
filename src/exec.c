/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/29 13:28:04 by eandela       #+#    #+#                 */
/*   Updated: 2024/12/13 17:25:18 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char	*ft_getenv(char *name, char **envp)
{
	int		i;
	char	*element;

	i = 0;
	element = NULL;
	while (envp && envp[i])
	{
		if (!ft_strncmp(name, envp[i], ft_strlen(name)))
			element = envp[i] + 1 + ft_strlen(name);
		i++;
	}
	return (element);
}

char	*get_path(char *command, char *full_path)
{
	char	**split_path;
	char	*path;
	char	*path_part;
	int		i;

	if (access(command, F_OK) == 0)
		return(command);
	split_path = ft_split(full_path, ':');
	i = 0;
	while (split_path[i])
	{
		path_part = ft_strjoin("/", command);
		path = ft_strjoin(split_path[i], path_part);
		free(path_part);
		if (access(path, F_OK) == 0)
		{
			ft_free_dbl(split_path);
			return (path);
		}
		free(path);
		path = NULL;
		i++;
	}
	ft_free_dbl(split_path);
	return (path);
}

void print_list(t_command *cmd_list)
{
	if (!cmd_list)
		return ;
	while (cmd_list)
	{
		printf("%s\n", cmd_list->args[0]);
		cmd_list = cmd_list->next;
	}
	printf("\n");
}

int	count_cmds(t_command *cmd_list)
{
	int i = 0;
	
	while (cmd_list)
	{
		i++;
		cmd_list = cmd_list->next;
	}
	return (i);
}

int **create_pipes(int num_pipes)
{
	int **pipes;
	int i;

	i = 0;
	if (num_pipes > 0)
		pipes = malloc(sizeof(int *) * num_pipes);
	else
		return NULL;
	if (!pipes)
		return NULL;
	while (i < num_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			while (i >= 0)
			{
				free(pipes[i]);
				i--;
			}
			return NULL;
		}
		if (pipe(pipes[i]) == -1) 
		{
			while (i >= 0)
			{
				free(pipes[i]);
				i--;
			}
            perror("pipe failed");
            return NULL;
        }
		i++;
	}
	return (pipes);
}

int handle_redirections(t_redirections *red_list)
{
	int file;
	int og_stdin;
	
	og_stdin = dup(STDIN_FILENO);	
	while (red_list)
	{
		if (red_list->type == IN_REDIRECT)
		{
			file = open(red_list->file, O_RDONLY);
			if (file == -1)
			{
				perror("asdfsadf");
				return (-1);
			}
			dup2(file, STDIN_FILENO);
			close(file);
		}
		else if (red_list->type == OUT_REDIRECT)
		{
			file = open(red_list->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (file == -1)
			{
				perror("open ");
				return (-1);
			}
			dup2(file, STDOUT_FILENO);
			close(file);
		}
		else if (red_list->type == OUT_APPEND)
		{
			file = open(red_list->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (file == -1)
			{
				perror("open append file failed");
				return (-1);
			}
			dup2(file, STDOUT_FILENO);
			close(file);
		}
		else if (red_list->type == HERE_DOC)
		{
			dup2(og_stdin, STDIN_FILENO);
			handle_here_doc(red_list);
		}
		red_list = red_list->next;
	}
	return (0);
}

void handle_pipes(int **pipes, t_command *cmd_list, int size)
{
	int i;
	int j;

	i = cmd_list->index;
	j = 0;
	if (i != 0)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
	}
	if (i != size)
	{
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	while (j < size)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void close_pipes(int **pipes, int size)
{
	int i;
	i = 0;
	while (i < size)
	{
		// dprintf(STDERR_FILENO, "closing fd: %i & %i\n", pipes[i][0], pipes[i][1]);
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	// close(STDOUT_FILENO);
	// close(STDIN_FILENO);
}

int	wait_for_children(void)
{
	int status;
	status = 0;
	while (wait(&status) != -1 || errno != ECHILD)
	{
		// printf("status: %i, %i\n", WEXITSTATUS(status), status);
	}
	// printf("final status: %i, %i\n", WEXITSTATUS(status), status);
	return (status);	
}

// void execute_cmds(t_command *cmd_list, t_env_list *env_list)
// {
// 	int id;
// 	int **pipes;
// 	int pipe_size ;
// 	char *path;

// 	pipe_size = count_cmds(cmd_list) - 1;
// 	pipes = create_pipes(pipe_size);
// 	id = -1;
// 	while (cmd_list)
// 	{
// 		id = fork();
// 		if (id == 0)
// 		{
// 			handle_pipes(pipes, cmd_list, pipe_size);
// 			if (handle_redirections(cmd_list->redirections) != 0)
// 				return ;
// 			if (is_builtin(cmd_list->args[0]))
// 			{
// 				execute_builtin(cmd_list->args, env_list);
// 				return;
// 			}
// 			if (cmd_list->args)
// 			{
// 				path = get_path(cmd_list->args[0], ft_getenv("PATH", ft_ll2arr(env_list)));
// 				if (!path)
// 				{
// 					perror("command not found");
// 					return;
// 				}
// 				// printf("path: %s\n", path);
// 				if (execve(path, cmd_list->args, ft_ll2arr(env_list)) == -1)
// 					perror("execve failed");
// 			}
// 		}
// 		cmd_list = cmd_list->next;
// 	}
// 	close_pipes(pipes, pipe_size);
// }

// int execute_builtin_command(t_command *cmd_list, t_env_list *env_list, int **pipes, int pipe_size)
// {
// 	int og_stdin = dup(STDIN_FILENO);
// 	int og_stdout = dup(STDOUT_FILENO);
// 	int status;
	
// 	handle_pipes(pipes, cmd_list, pipe_size);
// 	if ((status = handle_redirections(cmd_list->redirections)) != 0)
// 		return (status);
// 	status = execute_builtin(cmd_list->args, env_list);
// 	dup2(og_stdin, STDIN_FILENO);
// 	dup2(og_stdout, STDOUT_FILENO);
// 	close(og_stdin);
// 	close(og_stdout);
// 	return (status);
// }

// int execute_external_command(t_command *cmd_list, t_env_list *env_list, int **pipes, int pipe_size)
// {
// 	int id;
// 	char *path;
	
// 	id = fork();
// 	if (id == 0)
// 	{
// 		handle_pipes(pipes, cmd_list, pipe_size);
// 		if (handle_redirections(cmd_list->redirections) != 0)
// 			return (-1);
// 		if (cmd_list->args)
// 		{
// 			path = get_path(cmd_list->args[0], ft_getenv("PATH", ft_ll2arr(env_list)));
// 			if (!path)
// 			{
// 				perror("command not found");
// 				return (-1);
// 			}
// 			if (execve(path, cmd_list->args, ft_ll2arr(env_list)) == -1)
// 				perror("execve failed");
// 		}
// 	}
// 	return (0);
// }

// int execute_commands(t_command *cmd_list, t_env_list *env_list)
// {
// 	int **pipes;
// 	const int pipe_size = count_cmds(cmd_list) - 1;
	
// 	pipes = create_pipes(pipe_size);
// 	while (cmd_list)
// 	{
// 		if (is_builtin(cmd_list->args[0]))
// 		{
// 			execute_builtin_command(cmd_list, env_list, pipes, pipe_size);
// 		}
// 		else
// 		{
// 			execute_external_command(cmd_list, env_list, pipes, pipe_size);
// 		}			
// 		cmd_list = cmd_list->next;
// 	}
// 	close_pipes(pipes, pipe_size);
// 	return (0);
// }

// int execute_single_command(t_command *cmd_list, t_env_list *env_list)
// {
// 	int status;

// 	handle_redirections(cmd_list->redirections);
// 	if (is_builtin(cmd_list->args[0]))
// 	{
// 		status = execute_builtin(cmd_list->args, env_list);
// 	}
// 	else
// 	{
// 		status = execute_external_command(cmd_list, env_list, NULL, 0);
// 	}
// }

// int execute_commands(t_command *cmd_list, t_env_list *env_list)
// {
// 	const int pipe_size = count_cmds(cmd_list) - 1;
// 	int status;

// 	if (count_cmds(cmd_list) == 1)
// 		status = execute_single_command(cmd_list, env_list);
// 	else
// 		status = execute_piped_commands(cmd_list, env_list, pipe_size);
// 	return (status);
// }



// int main(int argc, char **argv, char **envp)
// {
// 	t_command *cmd_list;
// 	// t_envp *envp_list;

// 	// envp_list = ft_arr2ll(envp);
// 	// open_fds = open("fds_open.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	
// 	cmd_list = NULL;
// 	if (!argc && !argv && !envp)
// 		return (0);
// 	// printf("hogdsai");
// 	fill_cmd_list(&cmd_list);
// 	// print_list(cmd_list);
// 	// printf("commands: %i\n", count_cmds(cmd_list));
// 	execute_cmds(cmd_list, envp);
// 	// list_open_fds();
// 	// ft_pwd();
// 	wait(NULL);
// 	wait(NULL);
// 	wait(NULL);
// 	wait(NULL);
// 	wait(NULL);
// 	wait(NULL);
// 	wait(NULL);
// 	wait(NULL);
// 	return (250);
// }