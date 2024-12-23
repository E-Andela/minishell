/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/23 23:53:18 by eandela       #+#    #+#                 */
/*   Updated: 2024/12/23 19:30:06 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *new_name()
{
	static int i = 0;
	char *name;

	++i;
	name = ft_strjoin("/tmp/.heredoc", ft_itoa(i));
	if (!name)
		shell_exit(MALLOC_FAIL);
	return (name);
}

void	heredoc_loop(int fd, t_redirections *red_list)
{
	char *buffer;
	size_t len;

	init_heredoc_signals();
	while (1 && g_signal != SIGINT)
	{
		buffer = readline("> ");
		if (!buffer)
			break ;
		len = ft_max(ft_strlen(buffer), ft_strlen(red_list->file));
		if (!ft_strncmp(buffer, red_list->file, len))
		{
			free(buffer);
			break ;
		}
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	init_signals();
}

int create_heredoc_file(t_redirections *redirection)
{
	char *file_name;
	int fd;
	
	file_name = new_name();
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(file_name);
		return (-1);
	}
	heredoc_loop(fd, redirection);
	// printf("g_signal: %i\n", g_signal);
	if (g_signal == SIGINT)
	{
		// printf("return signal from heredoc\n");
		close(fd);
		unlink(file_name);
		free(file_name);
		return (130);
	}
	free(redirection->file);
	redirection->file = file_name;
	close(fd);
	return (0);
}

int	create_heredocs(t_command *cmd_list)
{
	t_redirections *redirection;
	int status;
	while (cmd_list)
	{
		redirection = cmd_list->redirections;
		while (redirection)
		{
			if (redirection->type == HERE_DOC)
				if ((status = create_heredoc_file(redirection)) != 0)
					return (status);
			redirection = redirection->next;
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}

int redirect_heredoc(t_redirections *redirection)
{
	int fd;
	
	fd = open(redirection->file, O_RDONLY);
	if (fd == -1)
	{
		unlink(redirection->file);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(redirection->file);
	return 0;	
}

// int handle_here_doc(t_redirections *red_list)
// {
// 	char *name;
// 	int fd;

// 	name = new_name();
// 	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		free(name);
// 		return (-1);
// 	}	
// 	heredoc_loop(fd, red_list);
// 	close(fd);
	
// 	fd = open(name, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		free(name);
// 		unlink(name);
// 		return (-1);
// 	}
// 	dup2(fd, STDIN_FILENO);
// 	close(fd);
// 	unlink(name);
// 	free(name);
// 	return (0);
// }
