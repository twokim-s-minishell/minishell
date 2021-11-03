/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 12:35:37 by kyunkim           #+#    #+#             */
/*   Updated: 2021/11/03 16:34:34 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	my_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
}

char	*ft_strdup(const char *src)
{
	int		length;
	char	*ptr;

	if (src == NULL)
		return (NULL);
	length = ft_strlen(src) + 1;
	ptr = (char *)malloc(sizeof(char) * length);
	if (ptr == NULL)
		return (NULL);
	my_strcpy(ptr, src);
	return (ptr);
}
