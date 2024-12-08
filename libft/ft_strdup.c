/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: eandela <marvin@42.fr>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 12:10:26 by eandela       #+#    #+#                 */
/*   Updated: 2024/09/01 19:06:53 by eandela       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		size;
	int		i;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	i = 0;
	ptr = (char *)malloc((size + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
