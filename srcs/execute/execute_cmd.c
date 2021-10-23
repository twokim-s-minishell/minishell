#include "minishell.h"

extern int	g_exit_code;

void	fork_process(t_info *info, int depth)
{
	info->pipex.pid[depth] = fork();
	if (info->pipex.pid[depth] == -1)
		error();
}

void	waiting_child_process(t_info *info)
{
	int	status;

	while (wait(&status) != -1)//모든 자식 프로세스가 끝날 때 까지 대기
	{
		;
	}
	g_exit_code = WEXITSTATUS(status);
}

void	execute_command(t_info *info, int depth)
{
	int	ret;

	info->cmd_sequence = depth;
	make_pipeline(info, depth);//pipe 생성
	fork_process(info, depth);//fork()
	if (info->pipex.pid[depth] > 0)
	{
		signal(SIGINT, SIG_IGN);
		if (depth == info->n_cmd - 1)//마지막 명령어이면 if문 진입
		{
			close_pipeline(info);//부모에서 파이프라인 다 닫음(자식엔 영향 없음)
			waiting_child_process(info);
			return ;//status값을 exitcode전역변수에 넣어주기
		}
		execute_command(info, depth + 1);//부모에서 execute_command() 함수 재귀 호출
	}
	if (info->pipex.pid[depth] == 0)
	{
		ret = execute_execve(info, depth);
		exit(ret);
	}
}

void	execute_command_main(t_info *info)
{
	init_pipe_fd(info);//2차원 int형 배열 동적할당
	info->pipex.pid = (int *)malloc(sizeof(int) * info->n_cmd);
	info->cmd_sequence = 0;
	get_cmd_list(info);
	if (is_builtin_command(info) && (info->n_cmd == 1))
	{
		g_exit_code = execute_execve(info, 0);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	execute_command(info, 0);
	signal(SIGINT, sig_handler);
}
