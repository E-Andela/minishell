#include "../../inc/minishell.h"

int	ft_cd(char **args, t_env_list *env_list)
{
	char *path;
	char *oldpwd;
	char tmp[PATH_MAX];

	if (!args[1])
	{
		path = getenv("HOME");
	}
	else
		path = args[1];
	if (path != NULL && path[0] != '\0')
	{
		if (chdir(path) == -1)
		{
			perror(path);
			return (1);
		}
	}
	return (0);
}