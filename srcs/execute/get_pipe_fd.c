/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyunkim <kyunkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:55:42 by kyunkim           #+#    #+#             */
/*   Updated: 2021/11/01 19:55:42 by kyunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 첫 번째 명령어는 파이프로 입력을 받는 경우가 없음
** 마지막 명령어는 파이프로 출력을 보내는 경우가 없음
*/
void	get_pipe_fd(t_info *info, int depth, int fd[])
{
	fd[READ] = STDIN_FILENO;
	fd[WRITE] = STDOUT_FILENO;
	if (depth != 0)
		fd[READ] = info->pipex.pipe_fd[depth - 1][READ];
	if (depth < (info->n_cmd - 1))
		fd[WRITE] = info->pipex.pipe_fd[depth][WRITE];
}
