/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:09:43 by eandela           #+#    #+#             */
/*   Updated: 2023/10/27 20:13:29 by eandela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*s3;
	size_t			i;
	const size_t	s1_len = ft_strlen(s1);
	const size_t	s2_len = ft_strlen(s2);

	i = 0;
	s3 = malloc(s1_len + s2_len + 1);
	if (s3 == NULL)
		return (NULL);
	while (i < s1_len)
	{
		s3[i] = s1[i];
		i++;
	}
	while (i < s1_len + s2_len)
	{
		s3[i] = s2[i - s1_len];
		i++;
	}
	s3[i] = '\0';
	return (s3);
}
