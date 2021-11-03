/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:55:10 by kyunkim           #+#    #+#             */
/*   Updated: 2021/11/03 21:09:30 by kyunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_exit_code	g_exit;

static void	incread_here_sequence(t_info *info)
{
	t_lst	*cur;

	cur = info->cmd_lst[info->cmd_sequence].redi;
	while (cur != NULL)
	{
		if (!ft_strncmp(cur->str, "<<", 2))
			info->here_sequence++;
		cur = cur->next;
	}
}

/*
** close_pipeline(info); 파이프 모두 닫음
	(마지막 재귀에서 닫기 때문에 그 전 재귀에서 실행된 자식프로세스에는 영향이 없다)
** waitpid() 함수로 모든 자식 프로세스가 끝날 때 까지 대기
** 자식 프로세스가 끝나면 wexitstatus() 함수에 status 넣어서 exit_code 구하기
** waitpid() 반환값이 -1이면 g_exit_code에 넣지말고 break ;
** 전역변수 g_exit_code에 exit_code 넣기
** 마지막 명령어의 상태코드만 넣어야되기 때문에 info->last_pid == ret를
   if문 조건식에 넣어서 마지막 프로세스 pid일 때만 g_exit_code 넣음
*/
static void	waiting_child_process(t_info *info, int depth)
{
	int	status;
	int	ret;

	ret = -1;
	info->last_pid = info->pipex.pid[depth];
	close_pipeline(info);
	while (TRUE)
	{
		ret = waitpid(0, &status, 0);
		if (ret == ERROR)
			break ;
		if (info->last_pid == ret && g_exit.sig_flag == FALSE)
			g_exit.code = wexitstatus(status);
	}
}

/*
** ./minishell 실행 시 부모에서 SIGUSR1 시그널을 무시해야됨
*/
static void	ignoring_sigusr1_command(t_info *info, int depth)
{
	signal(SIGUSR1, SIG_IGN);
	if (depth != info->n_cmd - 1)
		execute_command(info, depth + 1);
	waiting_child_process(info, depth);
	signal(SIGUSR1, execve_handler);
}

/*
** 1. 명령어가 2개 이상일 경우 make_pipeline()함수로 파이프 생성
** 2. fork_process() 함수로 자식 프로세스 생성(execve() 함수 실행하기 위함)
**    (exec 계열의 함수는 프로세스를 생성할 때 호출자를 삭제하고 프로세스를 생성하기 때문에 fork()하고 자식에서 실행해줘야한다.)
** 3. 부모프로세스에선 명령어 개수 만큼 반복해서 execute_command() 재귀 호출
** 4. 자식프로세스에선 execute_execve() 함수 들어가서 명령어 실행
*/
void	execute_command(t_info *info, int depth)
{
	if (depth > info->n_cmd - 1)
		return ;
	info->cmd_sequence = depth;
	make_pipeline(info, depth);
	fork_process(info, depth);
	if (info->pipex.pid[depth] > 0)
	{
		signal(SIGINT, SIG_IGN);
		incread_here_sequence(info);
		if (info->cmd_lst[depth].text != NULL
			&& !ft_strcmp("./minishell", info->cmd_lst[depth].text->str))
			ignoring_sigusr1_command(info, depth);
		else
		{
			if (depth == info->n_cmd - 1)
				waiting_child_process(info, depth);
			execute_command(info, depth + 1);
		}
	}
	else if (info->pipex.pid[depth] == 0)
	{
		signal(SIGUSR1, SIG_IGN);
		exit(execute_execve(info));
	}
}

/*
** 1. init_pipe_fd() 호출해서 파이프 fd 저정할 2차원 int형 배열 동적할당
** 2. 커맨드가 1개인데 빌트인 커맨드이면 execute_command() 함수 진입 안하고
**	  바로 execute_execve() 호출 후 리턴
** 3. 아니면 execute_command() 함수 진입
*/
void	execute_command_main(t_info *info)
{
	init_pipe_fd(info);
	g_exit.code = 0;
	g_exit.sig_flag = FALSE;
	info->pipex.here_flag = 0;
	info->cmd_sequence = 0;
	info->here_sequence = 0;
	info->pipex.pid = (int *)malloc(sizeof(int) * info->n_cmd);
	merror(info->pipex.pid);
	if (get_here_doc_count(info))
	{
		if (run_here_doc(info) == ERROR)
			return ;
	}
	if (is_builtin_command(info) && (info->n_cmd == 1))
	{
		g_exit.code = execute_execve(info);
		return ;
	}
	execute_command(info, 0);
}
