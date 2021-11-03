/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:32:19 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/03 21:14:38 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_string_size(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (ERROR);
	while (str[i] != NULL)
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*s1_tmp;
	unsigned char	*s2_tmp;

	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (0);
	s1_tmp = (unsigned char *)s1;
	s2_tmp = (unsigned char *)s2;
	if (s1 == NULL)
		return (-1 * s2_tmp[0]);
	if (s2 == NULL)
		return (s1_tmp[0]);
	while (s1_tmp[i] && s2_tmp[i])
	{
		if (s1_tmp[i] != s2_tmp[i])
			break ;
		i++;
	}
	return (s1_tmp[i] - s2_tmp[i]);
}

void	swap_str(char **str, int i, int j)
{
	char	*tmp;

	tmp = str[i];
	str[i] = str[j];
	str[j] = tmp;
}

void	sort_env_str(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i] != NULL)
	{
		j = i;
		while (str[j] && (ft_strcmp(str[j - 1], str[j]) > 0))
		{
			swap_str(str, j - 1, j);
			j--;
			if (j <= 0)
				break ;
		}
		i++;
	}
}
