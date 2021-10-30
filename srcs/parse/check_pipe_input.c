#include "minishell.h"

extern int	g_exit_code;

int	check_pipe_input(char **line)
{
	int		i;
	int		j;
	char	*add;
	char	*tmp;

	i = 0;
	while ((*line)[i] && (*line)[i] != '|')
		i++;
	if ((*line)[i] == '\0')
		return (NORMAL);
	j = i + 1;
	while (is_space((*line)[j]))
		j++;
	if ((*line)[j] == '\0')
	{
		signal(SIGINT, pipe_input_handler);
		while (TRUE)
		{
			add = readline("> ");
			if (g_exit_code == -42)
			{
				free(add);
				g_exit_code = 1;
				return (ERROR);
			}
			if (add == NULL)
			{
				ft_putstr_fd("\x1b[1A", STDERR_FILENO);
				ft_putstr_fd("\033[2C", STDERR_FILENO);
				error_message("syntax error", NULL, "unexpected end of file");
				return (ERROR);
			}
			if (add[0] != '\0')
				break ;
		}
		tmp = *line;
		*line = ft_strjoin(tmp, add);
		merror(*line);
		free(add);
		free(tmp);
	}
	return (NORMAL);
}
//경우 체크 -> 파이프 만나고 그 뒤에 스페이스나 아무것도 없는 경우
//인풋 리드라인으로 받음.
//두 문자열 join
//라인에 새로 할당
//시그널 처리 추가