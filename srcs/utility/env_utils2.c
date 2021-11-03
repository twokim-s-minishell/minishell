/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:28:58 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/03 20:14:15 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_env_path(t_info *info)
{
	free_double_string(info->env_path);
	info->env_path = NULL;
	set_environment_path(info);
}

void	print_env_str(char **str, int *fd)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		ft_putendl_fd(str[i], fd[WRITE]);
		i++;
	}
}

int	incorrect_env_key(char *env_key)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(env_key[i]) || env_key[i] == '_'))
		return (TRUE);
	while ((ft_isalpha(env_key[i]) || env_key[i] == '_'
			|| ft_isdigit(env_key[i])))
		i++;
	if (env_key[i] == '+')
		i++;
	if (env_key[i] == 0)
		return (FALSE);
	return (TRUE);
}

int	check_add_value(char **env)
{
	int		len;
	char	*tmp;

	len = (int)ft_strlen(env[KEY]);
	if (env[KEY][len - 1] == '+')
	{
		tmp = (char *)malloc(sizeof(char) * len);
		merror(tmp);
		ft_strlcpy(tmp, env[KEY], len);
		free(env[KEY]);
		env[KEY] = tmp;
		return (TRUE);
	}
	return (FALSE);
}

void	reset_env_info(t_info *info)
{
	free_double_string(info->env_str);
	make_env_double_string(info);
	reset_env_path(info);
}
