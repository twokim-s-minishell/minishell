/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:55:44 by kyunkim           #+#    #+#             */
/*   Updated: 2021/11/03 21:17:57 by kyunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 1. fork() 함수로 자식 프로세스 생성
** 2. pipe() 함수로 파이프 생성하고 이 파이프에다가 문자열 저장
** 3. 자식 프로세스에서 limiter 입력받을 때 까지 readline()으로 문자열 입력받음
** 4. readline()으로 입력받는 중 시그널 처리 위해 signal(SIGINT, here_doc_handler) 추가
** 5. 만약 SIGINT 시그널을 받으면 자식프로세스가 exit(254) 를 하게함.
** 6. if (wexitstatus(status) == 254) 로 시그널을 입력받았는지 판단
** 7. readline() 중 SIGINT를 받으면 명령어 실행하면 안되고 멈춰야되니까 일부로 -2를 리턴해서
	  플래그를 줌
** 8. 정상 종료 시 fd[1] 닫고 파이프 fd[0]을 반환
*/
static int	read_string_from_stdin(char *limiter, int pipe_fd[])
{
	char	*str;

	signal(SIGINT, here_doc_handler);
	while (TRUE)
	{
		str = readline(">");
		if (str == NULL || ft_strcmp(str, limiter) == 0)
			break ;
		ft_putendl_fd(str, pipe_fd[WRITE]);
		free(str);
		str = NULL;
	}
	exit(1);
}

int	here_doc(t_info *info, char *limiter)
{
	int		pipe_fd[2];
	int		pid;
	int		status;

	info->pipex.is_here_doc = 1;
	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		wait(&status);
		if (wexitstatus(status) == 254)
			return (ERROR);
	}
	else if (pid == 0)
		read_string_from_stdin(limiter, pipe_fd);
	info->pipex.is_here_doc = 0;
	close(pipe_fd[WRITE]);
	return (pipe_fd[READ]);
}

int	get_here_doc_count(t_info *info)
{
	int		idx;
	int		here_doc_cnt;
	t_lst	*cur;

	idx = 0;
	here_doc_cnt = 0;
	while (idx < info->n_cmd)
	{
		cur = info->cmd_lst[idx].redi;
		while (cur != NULL)
		{
			if (ft_strcmp(info->cmd_lst[idx].redi->str, "<<"))
				here_doc_cnt++;
			cur = cur->next;
		}
		idx++;
	}
	return (here_doc_cnt);
}

int	check_here_doc(t_info *info, t_lst *cur, int *here_doc_cnt)
{
	char	**redi;

	redi = ft_split(cur->str, '\"');
	if (!ft_strcmp(redi[0], "<<"))
	{
		info->pipex.here_fd[*here_doc_cnt] = here_doc(info, redi[1]);
		if (info->pipex.here_fd[*here_doc_cnt] == ERROR)
		{
			free_double_string(redi);
			redi = NULL;
			return (ERROR);
		}
		(*here_doc_cnt)++;
	}
	free_double_string(redi);
	redi = NULL;
	return (NORMAL);
}

int	run_here_doc(t_info *info)
{
	t_lst	*cur;
	int		idx;
	int		here_doc_cnt;

	idx = 0;
	here_doc_cnt = 0;
	init_here_fd(info);
	while (idx < info->n_cmd)
	{
		cur = info->cmd_lst[idx].redi;
		while (cur != NULL)
		{
			if (check_here_doc(info, cur, &here_doc_cnt) == ERROR)
				return (ERROR);
			cur = cur->next;
		}
		idx++;
	}
	return (NORMAL);
}
