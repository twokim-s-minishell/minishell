/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:57:17 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/01 14:59:12 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(char **cmd, t_info *info, int *fd)
{
	int		ret;

	ret = TRUE;
	if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd[1], info);
	else if (!ft_strcmp(cmd[0], "pwd"))
		pwd(fd, info);
	else if (!ft_strcmp(cmd[0], "export"))
		export(cmd, info, fd);
	else if (!ft_strcmp(cmd[0], "unset"))
		unset(cmd, info);
	else if (!ft_strcmp(cmd[0], "env"))
		env(info, fd);
	else if (!ft_strcmp(cmd[0], "exit"))
		execute_exit(cmd, info);
	else if (!ft_strcmp(cmd[0], "echo"))
		echo(info, fd);
	else if (is_register_variable(cmd[0]))
		register_variable(cmd[0], info, fd);
	else
		ret = FALSE;
	free_double_string(info->cmd_str);
	info->cmd_str = NULL;
	return (ret);
}
