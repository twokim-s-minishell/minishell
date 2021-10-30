#include "minishell.h"

int	builtin(char **cmd, t_info *info, int *fd)
{
	int		cmd_len;
	int		ret;

	cmd_len = ft_strlen(cmd[0]) + 1;
	ret = TRUE;
	if (!ft_strncmp(cmd[0], "cd", cmd_len))
		cd(cmd[1], info);
	else if (!ft_strncmp(cmd[0], "pwd", cmd_len))
		pwd(fd, info);
	else if (!ft_strncmp(cmd[0], "export", cmd_len))
		export(cmd, info, fd);
	else if (!ft_strncmp(cmd[0], "unset", cmd_len))
		unset(cmd, info);
	else if (!ft_strncmp(cmd[0], "env", cmd_len))
		env(info, fd);
	else if (!ft_strncmp(cmd[0], "exit", cmd_len))
		execute_exit(cmd, info);
	else if (!ft_strncmp(cmd[0], "echo", cmd_len))
		echo(info, fd);
	else if (is_register_variable(cmd[0]))
		register_variable(cmd[0], info, fd);
	else
		ret = FALSE;//명령어 없을때
	free_double_string(info->cmd_str);
	info->cmd_str = NULL;
	return (ret);
}
