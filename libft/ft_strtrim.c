/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:28:56 by eandela           #+#    #+#             */
/*   Updated: 2023/10/23 15:19:41 by eandela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*new;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end >= 0 && ft_strchr(set, s1[end]))
		end--;
	if (end < 0)
	{
		new = malloc(1);
		if (!new)
			return (NULL);
		new[0] = '\0';
	}
	else
	{
		new = malloc(end - start + 2);
		if (!new)
			return (NULL);
		ft_strlcpy(new, &s1[start], end - start + 2);
	}
	return (new);
}
