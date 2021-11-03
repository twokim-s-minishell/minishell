/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:07:23 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/03 21:13:40 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_exit_code	g_exit;

void	del_env_variable(t_env *cur, t_info *info)
{
	t_env	*pre;
	t_env	*next;

	pre = cur->prev;
	next = cur->next;
	if (info->env_deq->head == cur)
		info->env_deq->head = info->env_deq->head->next;
	if (info->env_deq->last == cur)
		info->env_deq->last = info->env_deq->last->prev;
	link_env_node(pre, next);
	if (cur->env_flag == TRUE)
		info->env_deq->size -= 1;
	if (cur->key)
		free(cur->key);
	if (cur->value)
		free(cur->value);
	free(cur);
}

int	unset(char **cmd, t_info *info)
{
	int		i;
	char	*key;
	t_env	*cur;

	i = 0;
	while (cmd[++i] != NULL)
	{
		key = cmd[i];
		if (incorrect_env_key(key))
		{
			error_msg(cmd[0], key, "not a valid identifier");
			g_exit.code = 1;
			continue ;
		}
		cur = check_listin(key, info);
		if (cur)
			del_env_variable(cur, info);
	}
	reset_env_info(info);
	return (g_exit.code);
}
