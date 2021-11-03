/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_here_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyunkim <kyunkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:53:44 by kyunkim           #+#    #+#             */
/*   Updated: 2021/11/03 20:58:24 by kyunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_here_fd(t_info *info)
{
	int		here_doc_cnt;

	here_doc_cnt = get_here_doc_count(info);
	if (here_doc_cnt)
	{
		info->pipex.here_fd = (int *)malloc(sizeof(int) * here_doc_cnt);
		merror(info->pipex.here_fd);
		ft_memset(info->pipex.here_fd, 0, here_doc_cnt);
	}
}
