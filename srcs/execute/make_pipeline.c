/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyunkim <kyunkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:55:49 by kyunkim           #+#    #+#             */
/*   Updated: 2021/11/01 19:55:49 by kyunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe_fd(t_info *info)
{
	int	idx;

	idx = 0;
	if (info->n_cmd > 1)
	{
		info->pipex.pipe_fd = (int **)malloc(sizeof(int *) * info->n_cmd - 1);
		merror(info->pipex.pipe_fd);
		while (idx < info->n_cmd - 1)
		{
			info->pipex.pipe_fd[idx] = (int *)malloc(sizeof(int) * 2);
			info->pipex.pipe_fd[idx][READ] = STDIN_FILENO;
			info->pipex.pipe_fd[idx][WRITE] = STDOUT_FILENO;
			merror(info->pipex.pipe_fd[idx]);
			idx++;
		}
	}
}

void	make_pipeline(t_info *info, int depth)
{
	char	*error_message;

	if (depth < (info->n_cmd - 1))
	{
		if (pipe(info->pipex.pipe_fd[depth]) < 0)
		{
			error_message = strerror(errno);
			ft_putendl_fd((char *)error_message, STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
}
