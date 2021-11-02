/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_stdio.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyunkim <kyunkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:55:54 by kyunkim           #+#    #+#             */
/*   Updated: 2021/11/02 17:45:42 by kyunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	switch_stdio(t_info *info, int fd[])
{
	int		ret;

	get_pipe_fd(info, info->cmd_sequence, fd);
	if (redirection(info, fd) == ERROR)
		return (TRUE);
	if (!ft_strcmp(info->cmd_str[0], "./minishell"))
		fd[WRITE] = STDOUT_FILENO;
	if (!is_builtin_command(info))
	{
		if (fd[READ] != STDIN_FILENO)
			ret = dup2(fd[READ], STDIN_FILENO);
		if (fd[WRITE] != STDOUT_FILENO)
			ret = dup2(fd[WRITE], STDOUT_FILENO);
		if (ret == -1)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		close_pipeline(info);
	}
	return (NORMAL);
}
