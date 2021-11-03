/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:21:15 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/03 21:21:16 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	make_export_string(t_env *cur, char **str)
{
	int		i;
	char	*front;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (cur != NULL)
	{
		if (cur->env_flag == TRUE)
		{
			front = ft_strjoin(cur->key, "=");
			merror(front);
			tmp = ft_strjoin("\"", cur->value);
			merror(tmp);
			tmp2 = ft_strjoin(tmp, "\"");
			merror(tmp2);
			str[i] = ft_strjoin(front, tmp2);
			merror(str[i++]);
			free(front);
			free(tmp);
			free(tmp2);
		}
		cur = cur->next;
	}
}

void	print_export(t_info *info, int *fd)
{
	int		i;
	t_env	*cur;
	char	**str;

	i = 0;
	cur = info->env_deq->head;
	str = (char **)malloc(sizeof(char *) * (info->env_deq->size + 1));
	merror(str);
	str[info->env_deq->size] = NULL;
	make_export_string(cur, str);
	sort_env_str(str);
	print_env_str(str, fd);
	free_double_string(str);
}
