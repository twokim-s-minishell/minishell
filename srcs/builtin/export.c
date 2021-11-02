/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:06:59 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/02 18:40:04 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_exit_code	g_exit;

void	print_export(t_info *info, int *fd)
{
	int		i;
	t_env	*cur;
	char	*tmp;
	char	**str;

	i = 0;
	cur = info->env_deq->head;
	str = (char **)malloc(sizeof(char *) * (info->env_deq->size + 1));
	merror(str);
	str[info->env_deq->size] = NULL;
	while (cur != NULL)
	{
		if (cur->env_flag == TRUE)
		{
			tmp = ft_strjoin(cur->key, "=");
			merror(tmp);
			str[i] = ft_strjoin(tmp, cur->value);
			merror(str[i++]);
			free(tmp);
		}
		cur = cur->next;
	}
	sort_env_str(str);
	print_env_str(str, fd);
	free_double_string(str);
}

void	add_env_value(char **env, t_env *cur, int add)
{
	char	*del;
	char	*new;

	if (env[VALUE][0] == '\0')
	{
		if (cur != NULL)
			cur->env_flag = TRUE;
		return ;
	}
	if (add == TRUE)
	{
		del = cur->value;
		new = ft_strjoin(cur->value, env[VALUE]);
		merror(new);
		cur->value = new;
		free(del);
	}
	else
	{
		if (cur->value)
			free(cur->value);
		cur->value = ft_strdup(env[VALUE]);
		merror(cur->value);
	}
	cur->env_flag = TRUE;
}

void	add_new_env(char **env, t_info *info)
{
	t_env	*end;
	t_env	*tmp;

	end = info->env_deq->last;
	tmp = create_env_node();
	link_env_node(end, tmp);
	end = end->next;
	end->key = ft_strdup(env[KEY]);
	merror(end->key);
	info->env_deq->last = end;
	end->env_flag = TRUE;
	info->env_deq->size += 1;
	if (env[VALUE] == NULL || env[VALUE][0] == '\0')
		return ;
	end->value = ft_strdup(env[VALUE]);
	merror(end->value);
}

static void	fillin_new_env(char	**env, t_info *info, int add_flag)
{
	t_env	*cur_env;

	cur_env = check_listin(env[KEY], info);
	if (cur_env)
		add_env_value(env, cur_env, add_flag);
	else
		add_new_env(env, info);
}

int	export(char **cmd, t_info *info, int *fd)
{
	int		i;
	int		add_flag;
	char	**env;

	i = 0;
	add_flag = FALSE;
	if (cmd[1] == NULL)
	{
		print_export(info, fd);
		return (NORMAL);
	}
	while (cmd[++i] != NULL)
	{
		env = env_split(cmd[i]);
		add_flag = check_add_value(env);
		if (incorrect_env_key(env[KEY]))
			g_exit.code = error_msg("export", env[0], "not a valid identifier");
		else
			fillin_new_env(env, info, add_flag);
		free_double_string(env);
	}
	reset_env_info(info);
	return (g_exit.code);
}
