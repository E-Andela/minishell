/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/05 20:07:41 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/05 21:08:53 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	**allocate_pipes(int num_pipes)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * num_pipes);
	if (!pipes)
		return (NULL);
	i = 0;
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
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

int	initialize_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			while (i >= 0)
			{
				free(pipes[i]);
				i--;
			}
			free(pipes);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	**create_pipes(int num_pipes)
{
	int	**pipes;

	pipes = allocate_pipes(num_pipes);
	if (!pipes)
		return (NULL);
	if (initialize_pipes(pipes, num_pipes) == -1)
		return (NULL);
	return (pipes);
}

void	handle_pipes(int **pipes, t_command *cmd_list, int size)
{
	int	i;
	int	j;

	i = cmd_list->index;
	j = 0;
	if (i != 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i != size)
		dup2(pipes[i][1], STDOUT_FILENO);
	while (j < size)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	close_pipes(int **pipes, int size)
{
	int	i;

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
