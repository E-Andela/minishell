/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/23 23:53:18 by eandela       #+#    #+#                 */
/*   Updated: 2024/12/19 22:02:26 by eandela       ########   odam.nl         */
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

	while (1)
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
}

int handle_here_doc(t_redirections *red_list)
{
	char *name;
	int fd;

	name = new_name();
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(name);
		return (-1);
	}	
	heredoc_loop(fd, red_list);
	close(fd);
	
	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		free(name);
		unlink(name);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(name);
	free(name);
	return (0);
}
