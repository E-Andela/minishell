/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/05 20:34:32 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/05 21:27:43 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_in_redirection(t_redirections *red_list)
{
	int	file;

	file = open(red_list->file, O_RDONLY);
	if (file == -1)
	{
		perror(red_list->file);
		return (1);
	}
	dup2(file, STDIN_FILENO);
	close(file);
	return (0);
}

int	handle_out_redirection(t_redirections *red_list)
{
	int	file;

	file = open(red_list->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
	{
		perror(red_list->file);
		return (1);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	return (0);
}

int	handle_out_append(t_redirections *red_list)
{
	int	file;

	file = open(red_list->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file == -1)
	{
		perror(red_list->file);
		return (1);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	return (0);
}

int	handle_here_doc(t_redirections *red_list)
{
	int	file;

	file = open(red_list->file, O_RDONLY);
	if (file == -1)
	{
		unlink(red_list->file);
		perror(red_list->file);
		return (1);
	}
	dup2(file, STDIN_FILENO);
	close(file);
	unlink(red_list->file);
	return (0);
}

int	handle_redirections(t_redirections *red_list)
{
	while (red_list)
	{
		if (red_list->type == IN_REDIRECT)
			if (handle_in_redirection(red_list) != 0)
				return (1);
		if (red_list->type == OUT_REDIRECT)
			if (handle_out_redirection(red_list) != 0)
				return (1);
		if (red_list->type == OUT_APPEND)
			if (handle_out_append(red_list) != 0)
				return (1);
		if (red_list->type == HERE_DOC)
			if (handle_here_doc(red_list) != 0)
				return (1);
		red_list = red_list->next;
	}
	return (0);
}
