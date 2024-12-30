#include "../../inc/minishell.h"
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

	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
			return(command);
		else
			return (NULL);
	}	
	split_path = ft_split(full_path, ':');
	i = 0;
	while (split_path[i])
	{
		path_part = ft_strjoin("/", command);
		path = ft_strjoin(split_path[i], path_part);
		if (!path_part || !path)
			shell_exit(MALLOC_FAIL);
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
	pipes = malloc(sizeof(int *) * num_pipes);
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
				perror(red_list->file);
				return (1);
			}
			dup2(file, STDIN_FILENO);
			close(file);
		}
		else if (red_list->type == OUT_REDIRECT)
		{
			file = open(red_list->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (file == -1)
			{
				perror(red_list->file);
				return (1);
			}
			dup2(file, STDOUT_FILENO);
			close(file);
		}
		else if (red_list->type == OUT_APPEND)
		{
			file = open(red_list->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (file == -1)
			{
				perror(red_list->file);
				return (1);
			}
			dup2(file, STDOUT_FILENO);
			close(file);
		}
		else if (red_list->type == HERE_DOC)
		{
			dup2(og_stdin, STDIN_FILENO);
			redirect_heredoc(red_list);
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
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	if (size > 0)
		free(pipes);
}

int	wait_for_children(t_command *cmd_list)
{
	int status;
	status = 0;
	while (cmd_list)
	{
		waitpid(cmd_list->pid, &status, 0);
		cmd_list = cmd_list->next;
	}
	if (status == 2 && g_signal == SIGINT)
		return (130);
	if (status == 131 && g_signal == SIGQUIT)
		return (131);
	return (WEXITSTATUS(status));	
}