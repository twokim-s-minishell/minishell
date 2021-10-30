#include "minishell.h"

static int	check_incorrect_pipe(t_info *info)//**얘 필요한지 체크해보기
{
	int		i;
	t_cmd	*cmd_lst;

	i = 0;
	cmd_lst = info->cmd_lst;
	while (i < info->n_cmd)
	{
		//(cmd_lst[i].text->str == NULL || cmd_lst[i].text->str[0] == '\0')를 바꿈
		if (cmd_lst[i].text == NULL && cmd_lst[i].redi == NULL)
		{
			syntax_error('|');
			return (ERROR);
		}
		i++;
	}
	return (NORMAL);
}

static int	all_is_space(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (line[i] == '\0')
		return (TRUE);
	return (FALSE);
}

int	parse_line(char *line, t_info *info)
{
	char	*new_line;

	if (all_is_space(line) || check_incorrect_line(line))
	{
		free(line);
		return (ERROR);
	}
	new_line = pre_processing(line, info);
	make_command(new_line, info);
	return (NORMAL);
}
