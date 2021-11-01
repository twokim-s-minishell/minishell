/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:31:44 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/01 15:31:45 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_env_double_string(t_info *info)
{
	int		i;
	char	*tmp;
	t_env	*cur;

	info->env_str = (char **)malloc(sizeof(char *) * (info->env_deq->size + 1));
	merror(info->env_str);
	i = 0;
	cur = info->env_deq->head;
	while (cur)
	{
		if (cur->env_flag == TRUE)
		{
			tmp = ft_strjoin(cur->key, "=");
			merror(tmp);
			info->env_str[i] = ft_strjoin(tmp, cur->value);
			merror(info->env_str[i]);
			free(tmp);
			tmp = 0;
			i++;
		}
		cur = cur->next;
	}
	info->env_str[i] = NULL;
}

void	save_env_variables(t_info *info, char **envp)
{
	int			size;
	t_env		*new;
	t_env		*cur;
	t_env_deq	*deq;

	new = make_env_list(envp);
	deq = (t_env_deq *)malloc(sizeof(t_env_deq));
	merror(deq);
	deq->head = new;
	cur = new;
	size = 0;
	while (cur != NULL)
	{
		size++;
		if (cur->next == NULL)
			deq->last = cur;
		cur = cur->next;
	}
	deq->size = size;
	info->env_deq = deq;
	make_env_double_string(info);
	info->home_path = get_env_value("HOME", info);
	info->pwd_path = getcwd(NULL, 0);
}
