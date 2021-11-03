/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyunkim <kyunkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:55:44 by kyunkim           #+#    #+#             */
/*   Updated: 2021/11/03 19:08:44 by kyunkim          ###   ########.fr       */
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

int	here_doc(t_info *info, char *limiter, int fd[])
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
			return (-2);
	}
	else if (pid == 0)
		read_string_from_stdin(limiter, pipe_fd);
	info->pipex.is_here_doc = 0;
	fd[READ] = pipe_fd[READ];
	close(pipe_fd[WRITE]);
	return (pipe_fd[READ]);
}

void	wait_here_doc(t_info *info, int depth)
{
	if (info->pipex.here_flag)
		waitpid(info->pipex.pid[depth - 1], NULL, 0);
}

void	is_here_doc(t_info *info, int depth)
{
	if (depth > 0)
	{
		if (info->cmd_lst[depth - 1].redi != NULL
			&& ft_strcmp(info->cmd_lst[depth - 1].redi->str, "<<"))
			info->pipex.here_flag = 1;
		wait_here_doc(info, depth);
	}
}
