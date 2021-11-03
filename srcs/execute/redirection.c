/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyunkim <kyunkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:55:51 by kyunkim           #+#    #+#             */
/*   Updated: 2021/11/03 20:52:37 by kyunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_here_doc_fd(t_info *info, int fd[])
{
	fd[READ] = info->pipex.here_fd[info->here_sequence];
	info->here_sequence++;
	return (fd[READ]);
}

static int	input_redirection(char *infile, int fd[])
{
	fd[READ] = open(infile, O_RDWR);
	if (fd[READ] == -1)
		return (ERROR);
	return (NORMAL);
}

static int	output_redirection(char *outfile, int fd[])
{
	fd[WRITE] = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd[WRITE] == -1)
		return (ERROR);
	return (NORMAL);
}

/*">>" 일 때는 open() 함수 옵션에 O_APPEND*/
static int	d_output_redirection(char *outfile, int fd[])
{
	fd[WRITE] = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd[WRITE] == -1)
		return (ERROR);
	return (NORMAL);
}

/*
** if (reval <= -1)//here_doc 상태에서 ctrl+c 받거나 open() 함수 에러났을 때 if문 들어감
*/
int	redirection(t_info *info, int fd[])
{
	t_lst	*cur;
	int		reval;
	char	**redi;

	cur = info->cmd_lst[info->cmd_sequence].redi;
	while (cur != NULL)
	{
		redi = ft_split(cur->str, '\"');
		if (!ft_strncmp(redi[0], "<<", 2))
			reval = get_here_doc_fd(info, fd);
		else if (!ft_strncmp(redi[0], ">>", 2))
			reval = d_output_redirection(redi[1], fd);
		else if (redi[0][0] == '<')
			reval = input_redirection(redi[1], fd);
		else if (redi[0][0] == '>')
			reval = output_redirection(redi[1], fd);
		if (reval <= -1)
		{
			if (reval == ERROR)
				error_msg(redi[1], NULL, strerror(errno));
			return (ERROR);
		}
		cur = cur->next;
	}
	return (NORMAL);
}
