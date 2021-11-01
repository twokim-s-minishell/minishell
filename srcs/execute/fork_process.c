/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyunkim <kyunkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:55:36 by kyunkim           #+#    #+#             */
/*   Updated: 2021/11/01 19:55:36 by kyunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_process(t_info *info, int depth)
{
	char	*error_message;

	info->pipex.pid[depth] = fork();
	if (info->pipex.pid[depth] == ERROR)
	{
		error_message = strerror(errno);
		ft_putendl_fd((char *)error_message, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
