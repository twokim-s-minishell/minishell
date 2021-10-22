#include "minishell.h"

void	reset_env_path(t_info *info)
{
	free_double_string(info->env_path);
	info->env_path = NULL;
	set_environment_path(info);
}