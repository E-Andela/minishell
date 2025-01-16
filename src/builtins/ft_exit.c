/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/03 14:34:04 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/16 17:00:01 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_too_many_args(void)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
}

void	exit_no_numeric_arg(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

int	ft_exit(char **args)
{
	int	i;

	i = 0;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (args[1])
	{
		if (args[2])
		{
			exit_too_many_args();
			return (1);
		}
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				exit_no_numeric_arg(args[1]);
				exit(2);
			}
			i++;
		}
		exit(ft_atoi(args[1]));
	}
	exit(0);
}
