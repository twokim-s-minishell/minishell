/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyunkim <kyunkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:03:34 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/02 15:16:55 by kyunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_string(char **list)
{
	int	i;

	i = 0;
	if (list == NULL)
		return ;
	while (list[i] != NULL)
		free(list[i++]);
	free(list);
}

void	clear_cmd_lst_node(t_lst *lst)
{
	t_lst	*cur;
	t_lst	*del;

	cur = lst;
	while (cur != NULL)
	{
		if (cur->str)
			free(cur->str);
		del = cur;
		cur = cur->next;
		free(del);
	}
}

void	clear_pipex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_cmd - 1)
	{
		if (info->pipex.pipe_fd == NULL
			|| info->pipex.pipe_fd[i] == NULL)
			break ;
		free(info->pipex.pipe_fd[i++]);
	}
	if (info->pipex.pipe_fd)
		free(info->pipex.pipe_fd);
	info->pipex.pipe_fd = NULL;
	if (info->pipex.pid)
		free(info->pipex.pid);
	if (info->pipex.here_doc_fd)
		free(info->pipex.here_doc_fd);
	info->pipex.pid = NULL;
}

void	clear_info(t_info *info)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = info->cmd_lst;
	if (info->cmd_str)
	{
		free_double_string(info->cmd_str);
		info->cmd_str = NULL;
	}
	while (i < info->n_cmd)
	{
		clear_cmd_lst_node(tmp[i].text);
		clear_cmd_lst_node(tmp[i].redi);
		i++;
	}
	free(info->cmd_lst);
	info->cmd_lst = NULL;
	clear_pipex(info);
}
