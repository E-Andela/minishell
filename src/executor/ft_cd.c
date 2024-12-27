#include "../../inc/minishell.h"

void set_pwd(t_env_list *env_list)
{
	t_env_list *pwd = ft_getenvp("PWD", env_list);
	char tmp[PATH_MAX];

	getcwd(tmp, PATH_MAX);
	if (pwd)
	{
		free(pwd->value);
		pwd->value = ft_strdup(tmp);
		if (!pwd->value)
			shell_exit(MALLOC_FAIL);
		return ;
	}
}

void set_oldpwd(t_env_list *env_list)
{
	t_env_list *oldpwd = ft_getenvp("OLDPWD", env_list);
	char tmp[PATH_MAX];

	getcwd(tmp, PATH_MAX);
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = ft_strdup(tmp);
		if (!oldpwd->value)
			shell_exit(MALLOC_FAIL);
		return ;
	}
}

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
		set_oldpwd(env_list);
		if (chdir(path) == -1)
		{
			perror(path);
			return (1);
		}
	}
	return (0);
}