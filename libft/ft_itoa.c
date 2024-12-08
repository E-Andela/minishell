/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:18:41 by eandela           #+#    #+#             */
/*   Updated: 2023/10/25 13:39:09 by eandela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_digits(long n);

char	*ft_itoa(int n)
{
	char	*array;
	int		digits;
	long	nb;

	nb = n;
	digits = ft_get_digits(nb);
	if (nb < 0)
	{
		digits++;
		nb *= -1;
	}
	array = (char *)malloc((digits + 1) * sizeof(char));
	if (!array)
		return (NULL);
	array[digits] = '\0';
	while (digits--)
	{
		array[digits] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (n < 0)
		array[0] = '-';
	return (array);
}

static int	ft_get_digits(long n)
{
	int	digits;

	digits = 1;
	if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}
