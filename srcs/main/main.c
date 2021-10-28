# include "minishell.h"

int	g_exit_code;

static void	add_slash_at_end_of_path(t_info *info, char **environment_path)
{
	int		idx;

	idx = 0;
	while (environment_path[idx])
	{
		info->env_path[idx] = ft_strjoin(environment_path[idx], "/");
		idx++;
	}
}

void	set_environment_path(t_info *info)
{
	int		idx;
	int		path_size;
	char	*path_value;
	char	**env_path;

	idx = 0;
	path_value = get_env_value("PATH", info);//에러 처리 추가
	if (path_value == NULL)
		return ;
	env_path = ft_split(path_value, ':');
	free(path_value);
	path_size = double_string_size(env_path);
	info->env_path = (char **)malloc(sizeof(char *) * (path_size + 1));
	merror(info->env_path);
	add_slash_at_end_of_path(info, env_path);
	info->env_path[path_size] = NULL;
	free_two_dimensional(env_path);
}

char	*get_command_line(void)
{
	char	*line;

	line = NULL;
	line = readline("Minishell >");
	if (line == NULL)//EOF(ctrl + d)만나면 NULL
	{
		ft_putstr_fd("\x1b[1A", STDOUT_FILENO);//커서 하나 위로
		ft_putstr_fd("\033[12C", STDOUT_FILENO);//커서 뒤로
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(0);
	}
	if (*line == 0)//엔터 눌렀을 때 함수 종료
	{
		free(line);
		return (NULL);
	}
	add_history(line);
	return (line);
}

void	get_line(t_info *info)
{
	char	*line;

	line = get_command_line();
	if (line == NULL)
		return ;
	if (parse_line(line, info))
		return ;
	execute_command_main(info);
	clear_info(info);
}

int	main(int arc, char *argv[], char *envp[])
{
	t_info	info;

	if (arc == 0 || argv == NULL)
		return (ERROR);
	ft_memset(&info, 0, sizeof(t_info));
	g_exit_code = 0;
	save_env_variables(&info, envp);
	set_environment_path(&info);
	signal(SIGUSR1, execve_handler);
	while (TRUE)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		get_line(&info);
	}
}
