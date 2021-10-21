#include "minishell.h"

int	pwd(int *fd, t_info *info)
{
	char	*cur_path;

	cur_path = getcwd(NULL, 0);
	if (cur_path == NULL)
	{
		cur_path = get_env_value("PWD", info);
		if (cur_path == NULL)
			error();//메시지 정하기
	}
	ft_putendl_fd(cur_path, fd[WRITE]);
	free(cur_path);
	return (NORMAL);
}
