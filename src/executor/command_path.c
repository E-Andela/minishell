/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/05 16:49:03 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/16 15:33:35 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*check_direct_path(char *command)
{
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
			return (command);
		else
			return (NULL);
	}
	return (NULL);
}

char	*join_path(char *path, char *command)
{
	char	*new_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		shell_exit(MALLOC_FAIL);
	new_path = ft_strjoin(tmp, command);
	if (!new_path)
		shell_exit(MALLOC_FAIL);
	free(tmp);
	return (new_path);
}

char	*search_path(char **split_path, char *command)
{
	char	*path;
	int		i;

	i = 0;
	while (split_path[i])
	{
		path = join_path(split_path[i], command);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		path = NULL;
		i++;
	}
	return (NULL);
}

char	*get_path(char *command, char *full_path)
{
	char	**split_path;
	char	*path;

	if (command[0] == '\0')
		return (NULL);
	path = check_direct_path(command);
	if (path)
		return (path);
	if (!full_path)
		return (NULL);
	split_path = ft_split(full_path, ':');
	if (!split_path)
		return (NULL);
	path = search_path(split_path, command);
	ft_free_dbl(split_path);
	return (path);
}
