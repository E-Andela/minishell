/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <eandela@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/03 18:48:45 by eandela       #+#    #+#                 */
/*   Updated: 2025/01/03 18:50:22 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	arg_counter(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}
