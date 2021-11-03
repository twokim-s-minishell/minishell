/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:57:17 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/03 20:06:41 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_command(t_info *info)
{
	char	*cmd;
	int		cmd_len;

	if (info->cmd_lst[info->cmd_sequence].text == NULL)
		return (FALSE);
	cmd = info->cmd_lst[info->cmd_sequence].text->str;
	cmd_len = ft_strlen(cmd);
	if (cmd_len <= 0)
		return (FALSE);
	if (!ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "echo")
		|| is_register_variable(info->cmd_lst[info->cmd_sequence].text))
		return (TRUE);
	return (FALSE);
}

int	builtin(char **cmd, t_info *info, int *fd)
{
	int		ret;

	ret = TRUE;
	if (!ft_strcmp(cmd[0], "cd"))
		ret = cd(cmd[1], info);
	else if (!ft_strcmp(cmd[0], "pwd"))
		ret = pwd(fd, info);
	else if (!ft_strcmp(cmd[0], "export"))
		ret = export(cmd, info, fd);
	else if (!ft_strcmp(cmd[0], "unset"))
		ret = unset(cmd, info);
	else if (!ft_strcmp(cmd[0], "env"))
		ret = env(info, fd);
	else if (!ft_strcmp(cmd[0], "exit"))
		ret = execute_exit(cmd, info);
	else if (!ft_strcmp(cmd[0], "echo"))
		ret = echo(info, fd);
	else if (is_register_variable(info->cmd_lst[info->cmd_sequence].text))
		ret = register_variable(cmd, info, fd);
	else
		ret = FALSE;
	free_double_string(info->cmd_str);
	info->cmd_str = NULL;
	return (ret);
}
