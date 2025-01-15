/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/29 14:13:39 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/15 15:59:50 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format_specefier(char placeholder, va_list arguments)
{
	if (placeholder == 'c')
		return (ft_print_char \
		(va_arg(arguments, int)));
	else if (placeholder == 's')
		return (ft_print_string \
		(va_arg(arguments, char *)));
	else if (placeholder == 'p')
		return (ft_print_pointer_address \
		(va_arg(arguments, unsigned long), placeholder));
	else if (placeholder == 'd' || placeholder == 'i')
		return (ft_print_number \
		(va_arg(arguments, int)));
	else if (placeholder == 'u')
		return (ft_print_unsigned_number \
		(va_arg(arguments, unsigned int)));
	else if (placeholder == 'x' || placeholder == 'X')
		return (ft_hexadecimal \
		(va_arg(arguments, unsigned int), placeholder));
	else if (placeholder == '%')
		return (ft_print_char('%'));
	else
		return (ft_printf("%%%c", placeholder));
}

int	ft_printf(const char *string_to_print, ...)
{
	int			i;
	int			char_count;
	va_list		arguments;

	if (string_to_print == NULL)
		return (-1);
	va_start (arguments, string_to_print);
	i = 0;
	char_count = 0;
	while (string_to_print[i] != '\0')
	{
		if (string_to_print[i] == '%')
		{
			if (string_to_print[i + 1] == '\0')
				return (-1);
			char_count += ft_format_specefier \
				(string_to_print[i + 1], arguments);
			i++;
		}
		else
			char_count += ft_print_char(string_to_print[i]);
		i++;
	}
	va_end(arguments);
	return (char_count);
}
