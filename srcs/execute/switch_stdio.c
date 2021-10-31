#include "minishell.h"

int	switch_stdio(t_info *info, int fd[])
{
	int		ret;

	get_pipe_fd(info, info->cmd_sequence, fd);
	if (redirection(info, fd) == ERROR)
		return (TRUE);
	if (!is_builtin_command(info))
	{
		if (fd[READ] != STDIN_FILENO)
			ret = dup2(fd[READ], STDIN_FILENO);
		if (fd[WRITE] != STDOUT_FILENO)
			ret = dup2(fd[WRITE], STDOUT_FILENO);
		if (ret == -1)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		close_pipeline(info);
	}
	return (NORMAL);
}
