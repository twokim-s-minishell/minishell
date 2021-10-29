#include "minishell.h"

void	close_pipeline(t_info *info)
{
	int	idx;

	idx = 0;
	while (idx < info->n_cmd - 1)
	{
		if (info->pipex.pipe_fd[idx][READ] != STDIN_FILENO)
			close(info->pipex.pipe_fd[idx][READ]);
		if (info->pipex.pipe_fd[idx][WRITE] != STDOUT_FILENO)
			close(info->pipex.pipe_fd[idx][WRITE]);
		idx++;
	}
}