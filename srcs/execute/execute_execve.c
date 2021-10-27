#include "minishell.h"

/*
** 파일이 존재하지 않거나 디렉토리 파일이면 에러메세지 출력 후 종료
*/
void	is_directory(char *cmd)
{
	struct stat	file_stat;
	int			file_type;

	if (stat(cmd, &file_stat) == ERROR)
	{
		error_message(cmd, NULL, strerror(errno));
		exit(CODE_NO_FILE_OR_DIR);
	}
	file_type = file_stat.st_mode & S_IFMT;
	if (file_type == S_IFDIR)
	{
		error_message(cmd, NULL, MSG_IS_A_DIR);
		exit(CODE_IS_A_DIR);
	}
}

/*
** 커맨드를 경로로 입력했을 때 커맨드를 그대로 리턴
** 아니면 while() 돌면서 PATH 환경변수를 참조해서 PATH 경로에 명령어 있으면 리턴
*/
char	*get_cmd_path(char **env_path, t_info *info)
{
	int			idx;
	char		*cmd;
	char		*path_of_cmd;
	struct stat	file_stat;

	idx = 0;
	path_of_cmd = NULL;
	cmd = info->cmd_str[0];
	if (cmd[0] == '\0')
		cmd = info->cmd_str[1];
	if (ft_strchr(cmd, '/'))
	{
		is_directory(cmd);
		return (cmd);
	}
	while (env_path && env_path[idx])
	{
		path_of_cmd = ft_strjoin(env_path[idx], cmd);
		if (stat(path_of_cmd, &file_stat) == 0)
			return (path_of_cmd);
		free(path_of_cmd);
		path_of_cmd = NULL;
		idx++;
	}
	return (path_of_cmd);
}

int	is_builtin_command(t_info *info)
{
	char	*cmd;
	int		cmd_len;

	cmd = info->cmd_str[0];
	cmd_len = ft_strlen(cmd);
	if (cmd_len <= 0)
		return (FALSE);
	if (!ft_strncmp(cmd, "cd", cmd_len)
		|| !ft_strncmp(cmd, "pwd", cmd_len)
		|| !ft_strncmp(cmd, "export", cmd_len)
		|| !ft_strncmp(cmd, "unset", cmd_len)
		|| !ft_strncmp(cmd, "env", cmd_len)
		|| !ft_strncmp(cmd, "exit", cmd_len)
		|| is_register_variable(cmd))
		return (TRUE);
	return (FALSE);
}

int	execute_execve(t_info *info, int depth)
{
	int		fd[2];
	char	*cmd_path;

	get_pipe_fd(info, depth, fd);
	if (redirection(info, fd) == ERROR)
		return (1);//현교 : 여기랑 여기 아래 리턴값 확인하기
	if (get_cmd_list(info) == ERROR)
		return (ERROR);
	cmd_path = get_cmd_path(info->env_path, info);
	if (!is_builtin_command(info))
		switch_stdio(info, fd[READ], fd[WRITE]);
	if (is_builtin_command(info))//**현교 : 이 if문 한 블록을 builtin함수 안에 넣어도 될듯?
	{
		builtin(info->cmd_str, info, fd);
		if (info->n_cmd > 1)
			exit(EXIT_SUCCESS);
		/*execve()는 알아서 프로세스가 교체되지만 builtin함수는 직접 exit을 해줘야한다. 안그러면 무한반복
		커맨드가 하나 일 때는 부모에서 실행되기 때문에 exit되면 안됨*/
	}
	else
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		// printf("path : %s\n", cmd_path);
		// printf("cmd_str : %s\n", info->cmd_str[0]);
		// printf("cmd_str : %s\n", info->cmd_str[1]);
		// printf("env_str : %s\n", info->env_str[0]);
		execve(cmd_path, info->cmd_str, info->env_str);
		error_message(info->cmd_str[0], NULL, MSG_CMD_NOT_FOUND);//++오류 확인하고 메시지 출력하는 함수로 변경
		exit(CODE_CMD_NOT_FOUND);
		//비정상 종료 리턴
	}
	free(cmd_path);
	return (NORMAL);
}
