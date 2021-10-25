#include "minishell.h"

int	pwd(int *fd, t_info *info)
{
	ft_putendl_fd(info->pwd_path, fd[WRITE]);
	return (NORMAL);
}
