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

int	check_correct_n_option(char *n_option)
{
	int	idx;

	idx = 2;
	if (ft_strncmp(n_option, "-n", 2))
		return (FALSE);
	while (n_option[idx])
	{
		if (n_option[idx] != 'n')
			return (FALSE);
		idx++;
	}
	return (TRUE);
}

void	echo_with_n(t_info *info, int *fd)
{
	int	idx;
	int	echo_len;

	idx = 2;
	echo_len = double_string_size(info->cmd_str);
	if (!(info->cmd_str[2]))
		return ;
	while (check_correct_n_option(info->cmd_str[idx]))
		idx++;
	while (info->cmd_str[idx])
	{
		ft_putstr_fd(info->cmd_str[idx], fd[WRITE]);
		if (idx < (echo_len - 1))
			ft_putstr_fd(" ", fd[WRITE]);
		idx++;
	}
}

void	echo(t_info *info, int *fd)
{
	int	idx;
	int	echo_len;

	idx = 1;
	echo_len = double_string_size(info->cmd_str);
	if (!(info->cmd_str[1]))
	{
		ft_putstr_fd("\n", fd[WRITE]);
		return ;
	}
	if (check_correct_n_option(info->cmd_str[1]))
	{
		echo_with_n(info, fd);
		return ;
	}
	while (info->cmd_str[idx])
	{
		ft_putstr_fd(info->cmd_str[idx], fd[WRITE]);
		if (idx < (echo_len - 1))
			ft_putstr_fd(" ", fd[WRITE]);
		idx++;
	}
	ft_putstr_fd("\n", fd[WRITE]);
}
