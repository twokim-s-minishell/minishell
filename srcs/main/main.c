# include "minishell.h"

int	g_exit_code;

static void	add_slash_at_end_of_path(t_info *info, char **environment_path)
{
	int		idx;
	char	*temp_for_substr;

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

void	get_line(t_info *info)
{
	char	*line;
	char	**command;
	int		pid;
	char	*str;

	line = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	//함수로 따로 따기
	// str = make_cursor_string();//주소 넣을거면 이걸로
	str = "Minishell >";
	line = readline(str);
	if (line == NULL)//EOF(ctrl + d)만나면 NULL
	{
		ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
		ft_putstr_fd("\033[12C", STDOUT_FILENO);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(0);
	}
	if (*line == 0)//엔터 눌렀을 때 함수 종료
	{
		free(line);
		return ;
	}
	if (line)
		add_history(line);
	if (parse_line(line, info))
	{
		error();//syntex에러 메시지 출력으로 변경하기
		return ;
	}
	execute_command_main(info);
	return ;
}

int	main(int arc, char *arvg[], char *envp[])
{
	char	*line;
	t_info	info;

	info.pipex.is_here_doc = 0;
	g_exit_code = 0;
	save_env_variables(&info, envp);
	set_environment_path(&info);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (TRUE)
	{
		get_line(&info);
	}
}
