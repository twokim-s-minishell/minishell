#include "minishell.h"

int	switch_stdio(t_info *info, int fd[])
{
	get_pipe_fd(info, info->cmd_sequence, fd);
	if (redirection(info, fd) == ERROR)
		return (TRUE);//현교 : 여기랑 여기 아래 리턴값 확인하기
	if (!is_builtin_command(info))
	{
		if (dup2(fd[READ], STDIN_FILENO) == -1)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		close_pipeline(info);
	}
	return (NORMAL);
}
