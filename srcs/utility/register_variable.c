/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:15:07 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/03 21:19:05 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_register_variable_string(char *cmd)
{
	char	**tmp;

	if (cmd == NULL)
		return (FALSE);
	if (ft_strchr(cmd, '=') != NULL)
	{
		tmp = env_split(cmd);
		if (!incorrect_env_key(tmp[KEY]))
		{
			free_double_string(tmp);
			return (TRUE);
		}
		free_double_string(tmp);
		tmp = NULL;
	}
	return (FALSE);
}

int	is_register_variable(t_lst *text)
{
	t_lst	*cur;

	cur = text;
	if (cur == NULL)
		return (FALSE);
	while (cur && is_register_variable_string(cur->str))
		cur = cur->next;
	if (cur != NULL)
		return (FALSE);
	return (TRUE);
}

int	register_variable(char **cmd, t_info *info, int *fd)
{
	int		i;
	int		flag;
	char	*export_cmd[3];
	char	**env;

	i = 0;
	while (cmd[i])
	{
		flag = FALSE;
		export_cmd[0] = "export";
		export_cmd[1] = ft_strdup(cmd[i]);
		merror(export_cmd[1]);
		export_cmd[2] = NULL;
		env = env_split(cmd[i++]);
		check_add_value(env);
		if (check_listin(env[KEY], info))
			flag = TRUE;
		free_double_string(env);
		export(export_cmd, info, fd);
		if (flag == FALSE)
			(info->env_deq->size)--;
		info->env_deq->last->env_flag = flag;
		free(export_cmd[1]);
	}
	return (NORMAL);
}
