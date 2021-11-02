/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyunkim <kyunkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:59:37 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/02 18:39:36 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_exit_code	g_exit;

static int	cd_old_pwd(t_info *info, int first_flag)
{
	char	*old_pwd;

	if (first_flag == 0)
	{
		error_msg("cd", NULL, "OLDPWD not set");
		g_exit.code = 1;
		return (ERROR);
	}
	old_pwd = get_env_value("OLDPWD", info);
	if (old_pwd == NULL)
	{
		error_msg("cd", NULL, "OLDPWD not set");
		g_exit.code = 1;
		return (ERROR);
	}
	if (chdir(old_pwd) == ERROR)
	{
		error_msg("cd", old_pwd, "No such file or directory");
		g_exit.code = 1;
		free(old_pwd);
		return (ERROR);
	}
	ft_putendl_fd(old_pwd, STDOUT_FILENO);
	free(old_pwd);
	return (TRUE);
}

static void	save_old_pwd(char *cur_pwd, t_info *info, int *first_flag)
{
	char	*cmd[3];
	int		fd[2];

	fd[0] = 0;
	fd[1] = 0;
	if (cur_pwd == NULL)
		return ;
	if (info->pwd_path)
	{
		free(info->pwd_path);
		info->pwd_path = NULL;
	}
	info->pwd_path = getcwd(NULL, 0);
	*first_flag += 1;
	cmd[0] = "export";
	if (cur_pwd)
		cmd[1] = ft_strjoin("OLDPWD=", cur_pwd);
	cmd[2] = NULL;
	export(cmd, info, fd);
	free(cmd[1]);
}

static void	just_cd(t_info *info, int *flag)
{
	char	*home;

	home = get_env_value("HOME", info);
	if (home == NULL)
	{
		error_msg("cd", NULL, "Home not set");
		g_exit.code = 1;
	}
	else if (chdir(home) == ERROR)
	{
		error_msg("cd", home, "No such file or directory");
		g_exit.code = 1;
	}
	else
		*flag = TRUE;
	free(home);
}

static void	home_cd(t_info *info, int *flag)
{
	if (chdir(info->home_path) == ERROR)
	{
		error_msg("cd", info->home_path, "No such file or directory");
		g_exit.code = 1;
	}
	else
		*flag = TRUE;
}

int	cd(char *path, t_info *info)
{
	int			normal_flag;
	static int	first_flag;
	char		cur_pwd[1024];

	normal_flag = FALSE;
	getcwd(cur_pwd, 1024);
	if (path == NULL)
		just_cd(info, &normal_flag);
	else if (path[0] == '~' && path[1] == 0)
		home_cd(info, &normal_flag);
	else if (path[0] == '-' && path[1] == 0)
	{
		if (cd_old_pwd(info, first_flag) != ERROR)
			normal_flag = TRUE;
	}
	else if (chdir(path) == ERROR)
		return (error_msg("cd", path, "No such file or directory"));
	else
		normal_flag = TRUE;
	if (normal_flag)
		save_old_pwd(cur_pwd, info, &first_flag);
	return (g_exit.code);
}
