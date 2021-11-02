/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:00:14 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/02 18:28:16 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_info *info, int *fd)
{
	t_env	*cur;

	cur = info->env_deq->head;
	while (cur != NULL)
	{
		if (cur->env_flag == TRUE && cur->value != NULL)
		{
			ft_putstr_fd(cur->key, fd[WRITE]);
			ft_putstr_fd("=", fd[WRITE]);
			ft_putendl_fd(cur->value, fd[WRITE]);
		}
		cur = cur->next;
	}
	return (NORMAL);
}
