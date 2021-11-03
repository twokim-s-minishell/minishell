/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:28:19 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/03 19:55:13 by hyeonkki         ###   ########.fr       */
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
