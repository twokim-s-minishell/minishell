/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyunkim <kyunkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:55:06 by kyunkim           #+#    #+#             */
/*   Updated: 2021/11/01 19:55:07 by kyunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipeline(t_info *info)
{
	int	idx;

	idx = 0;
	while (idx < info->n_cmd - 1)
	{
		if (info->pipex.pipe_fd[idx][READ] != STDIN_FILENO)
			close(info->pipex.pipe_fd[idx][READ]);
		if (info->pipex.pipe_fd[idx][WRITE] != STDOUT_FILENO)
			close(info->pipex.pipe_fd[idx][WRITE]);
		idx++;
	}
}
