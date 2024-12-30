#include "../../inc/minishell.h"

int	ft_exit(char **args)
{
	int i;

	i = 0;
	if (args[1])
	{
		if (args[2])
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			return (1);
		}
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				ft_putstr_fd("exit\n", STDERR_FILENO);
				ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
				ft_putstr_fd(args[1], STDERR_FILENO);
				ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
				exit(2);
			}
			i++;
		}
		exit(ft_atoi(args[1]));
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(0);
}
