/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_unsigned_number.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 16:22:26 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/15 15:59:47 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*uitoa_converter(unsigned int n, char *str, size_t n_len)
{
	size_t	num;

	num = n;
	str[n_len] = '\0';
	n_len -= 1;
	while (num != 0)
	{
		str[n_len] = (num % 10 + '0');
		num /= 10;
		n_len--;
	}
	return (str);
}

char	*ft_uitoa(unsigned int n, char *str)
{
	size_t	n_len;
	size_t	num;

	n_len = 0;
	num = n;
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	while (num != 0)
	{
		n_len++;
		num /= 10;
	}
	return (uitoa_converter(n, str, n_len));
}

int	ft_print_unsigned_number(unsigned int u)
{
	char	num[11];
	int		len;

	ft_uitoa(u, num);
	len = ft_strlen(num);
	return (write(1, num, len));
}
