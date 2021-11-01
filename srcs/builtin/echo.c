/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:00:07 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/01 15:00:08 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_with_n(t_info *info, int *fd)
{
	if (!(info->cmd_str[2]))
		return ;
	ft_putstr_fd(info->cmd_str[2], fd[WRITE]);
}

void	echo(t_info *info, int *fd)
{
	if (!(info->cmd_str[1]))
	{
		ft_putstr_fd("\n", fd[WRITE]);
		return ;
	}
	if (!ft_strcmp(info->cmd_str[1], "-n"))
	{
		echo_with_n(info, fd);
		return ;
	}
	ft_putstr_fd(info->cmd_str[1], fd[WRITE]);
	ft_putstr_fd("\n", fd[WRITE]);
}
