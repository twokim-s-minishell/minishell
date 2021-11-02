/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:28:19 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/02 18:29:23 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_split(char *str)
{
	int		key_len;
	char	*sep;
	char	**env;

	env = (char **)malloc(sizeof(char *) * 3);
	merror(env);
	sep = ft_strchr(str, '=');
	key_len = sep - str + 1;
	if (sep == NULL)
		key_len = ft_strlen(str) + 1;
	env[KEY] = (char *)malloc(sizeof(char) * key_len);
	merror(env[KEY]);
	ft_strlcpy(env[KEY], str, key_len);
	if (sep)
		env[VALUE] = ft_strdup(sep + 1);
	else
	{
		env[VALUE] = (char *)malloc(sizeof(char));
		env[VALUE][0] = '\0';
	}
	merror(env[VALUE]);
	env[2] = NULL;
	return (env);
}

t_env	*check_listin(char *env_key, t_info *info)
{
	int		len_value;
	t_env	*cur;

	len_value = (int)ft_strlen(env_key) + 1;
	cur = info->env_deq->head;
	while (cur != NULL)
	{
		if (!ft_strncmp(env_key, cur->key, len_value))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

char	*get_env_value(char *key, t_info *info)
{
	t_env	*cur;
	char	*ret;

	cur = check_listin(key, info);
	if (cur == NULL)
		return (NULL);
	ret = ft_strdup(cur->value);
	merror(ret);
	return (ret);
}

int	is_register_variable(char *cmd)
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
	}
	return (FALSE);
}

int	register_variable(char *cmd, t_info *info, int *fd)
{
	int		flag;
	char	*export_cmd[3];
	char	**env;

	flag = FALSE;
	export_cmd[0] = "export";
	export_cmd[1] = ft_strdup(cmd);
	merror(export_cmd[1]);
	export_cmd[2] = NULL;
	env = env_split(cmd);
	check_add_value(env);
	if (check_listin(env[KEY], info))
		flag = TRUE;
	free_double_string(env);
	export(export_cmd, info, fd);
	if (flag == FALSE)
		info->env_deq->last->env_flag = FALSE;
	free(export_cmd[1]);
	return (NORMAL);
}
