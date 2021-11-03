/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:55:39 by kyunkim           #+#    #+#             */
/*   Updated: 2021/11/03 20:03:53 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_cmd_list(t_info *info, t_lst **cur)
{
	int		cnt;
	t_lst	*tmp;

	cnt = 0;
	*cur = info->cmd_lst[info->cmd_sequence].text;
	if (*cur != NULL && !is_register_variable(*cur))
		while (is_register_variable_string((*cur)->str) && (*cur)->next)
			*cur = (*cur)->next;
	tmp = *cur;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		cnt++;
	}
	info->cmd_str = (char **)malloc(sizeof(char *) * (cnt + 1));
	merror(info->cmd_str);
	info->cmd_str[cnt] = NULL;
}

void	get_cmd_list(t_info *info)
{
	int		cnt;
	t_lst	*cur;

	cnt = 0;
	malloc_cmd_list(info, &cur);
	while (cur != NULL)
	{
		if (cur->str != NULL && cur->str[0] != '\0')
		{
			info->cmd_str[cnt] = ft_strdup(cur->str);
			merror(info->cmd_str[cnt]);
			cnt++;
		}
		cur = cur->next;
	}
	info->cmd_str[cnt] = NULL;
}
