/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/23 18:11:19 by eandela       #+#    #+#                 */
/*   Updated: 2024/12/12 17:41:21 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool is_n(char *arg)
{
	int i;

	i = 0;
	if (!arg)
		return (false);
	if (arg[i] != '-')
		return (false);
	i++;
	if (arg[i] != 'n')
		return (false);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return false;
		i++;
	}
	return (true);
}

int	ft_echo(char **arg)
{
	bool n;
	int i;
	
	n = false;
	i = 1;
	while (arg[i])
	{
		if (is_n(arg[i]))
			n = true;
		else
			break;
		i++;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return 0;
}

// int main(void)
// {
// 	char *arg[] = {"-nt", "-n", "-nnnnn", "-hello", "-nnn", NULL};
// 	ft_echo(arg);
// }