#include "minishell.h"

extern int	g_exit_code;

int	read_string_from_stdin(t_info *info, char *limiter)
{
	char	*str;
	int		pipe_fd[2];
	int		pid;
	int		status;

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		wait(&status);
		if (wexitstatus(status) == 127)
			return (0);
	}
	else if (pid == 0)
	{
		signal(SIGINT, here_doc_handler);
		while (TRUE)
		{
			str = readline(">");//readline으로 변경, ctrl + d받으면 NULL
			if (str == NULL || strcmp(str, limiter) == 0)//
				break ;
			ft_putendl_fd(str, pipe_fd[WRITE]);//받은 문자열을 파이프에 저장
			free(str);
			str = NULL;
		}
		exit(1);
	}
	info->pipex.is_here_doc = 0;
	close(pipe_fd[WRITE]);
	return (pipe_fd[READ]);//문자열이 저장된 파이프의 fd를 반환
}

int	here_doc(t_info *info, char *limiter, int fd[])
{
	info->pipex.is_here_doc = 1;
	fd[READ] = read_string_from_stdin(info, limiter);//파이프의 fd 리턴, 에러 시 -1 리턴
	if (fd[READ] == -1)
		return (ERROR);
	return (fd[READ]);
}
