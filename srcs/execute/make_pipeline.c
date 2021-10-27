#include "minishell.h"

void	init_pipe_fd(t_info *info)
{
	int		idx;

	idx = 0;
	info->pipex.pipe_fd = (int **)malloc(sizeof(int *) * info->n_cmd);
	merror(info->pipex.pipe_fd);
	while (idx < info->n_cmd)
	{
		info->pipex.pipe_fd[idx] = (int *)malloc(sizeof(int) * 2);
		merror(info->pipex.pipe_fd[idx]);
		idx++;
	}
}

int	make_pipeline(t_info *info, int depth)
{
	char	*error_message;

	if (pipe(info->pipex.pipe_fd[depth]) < 0)
	{
		error_message = strerror(errno);
		ft_putendl_fd((char *)error_message, STDERR_FILENO);
		return (ERROR);
	}
	return (NORMAL);
}
