/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_two_dimensional.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:03:37 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/01 20:03:38 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_two_dimensional(char **two_dimensional)
{
	int	idx;

	idx = 0;
	while (two_dimensional[idx])
	{
		if (two_dimensional[idx])
			free(two_dimensional[idx]);
		idx++;
	}
	if (two_dimensional)
		free(two_dimensional);
}
