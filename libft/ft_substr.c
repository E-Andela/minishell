/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:42:13 by eandela           #+#    #+#             */
/*   Updated: 2023/10/25 14:51:23 by eandela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new;
	size_t			size;
	size_t			i;
	unsigned int	str_len;

	size = 0;
	i = 0;
	str_len = ft_strlen(s);
	if (str_len <= start)
		size = 0;
	else
		while (s[size + start])
			size++;
	if (size <= len)
		len = size;
	new = (char *)malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
