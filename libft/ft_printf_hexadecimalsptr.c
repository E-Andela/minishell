/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_hexadecimalsptr.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/07 16:22:32 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/15 15:59:37 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_hexadecimal(unsigned long num, char placeholder)
{
	if (num >= 16)
	{
		ft_print_hexadecimal(num / 16, placeholder);
		ft_print_hexadecimal(num % 16, placeholder);
	}
	else
	{
		if (num <= 9)
			ft_print_char(num + '0');
		else
		{
			if (placeholder == 'x' || placeholder == 'p')
				ft_print_char(num - 10 + 'a');
			if (placeholder == 'X')
				ft_print_char(num - 10 + 'A');
		}
	}
}

int	ft_hexadecimal(unsigned long h, char placeholder)
{
	size_t	len;
	size_t	num;

	if (h == 0)
		return (write(1, "0", 1));
	num = h;
	len = 0;
	while (num != 0)
	{
		num /= 16;
		len++;
	}
	ft_print_hexadecimal(h, placeholder);
	return (len);
}

int	ft_print_pointer_address(unsigned long p, char placeholder)
{
	int	printed_chars;

	if ((void *)p == NULL)
		return (write(1, "(nil)", 5));
	printed_chars = (write(1, "0x", 2));
	printed_chars += ft_hexadecimal(p, placeholder);
	return (printed_chars);
}
