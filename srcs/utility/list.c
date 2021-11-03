/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:29:45 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/03 17:42:24 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*create_node(void)
{
	t_lst	*lst;

	lst = (t_lst *)malloc(sizeof(t_lst));
	merror(lst);
	lst->str = NULL;
	lst->next = NULL;
	return (lst);
}

void	link_node(char *cmd, t_lst **list)
{
	t_lst	*cur;
	t_lst	*tmp;

	cur = *list;
	tmp = create_node();
	tmp->str = ft_strdup(cmd);
	merror(tmp->str);
	if (cur == NULL)
		*list = tmp;
	else
	{
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = tmp;
	}
}
