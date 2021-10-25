#include "minishell.h"

int	check_incorrect_pipe(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_cmd)
	{
		if (info->cmd_lst[i].text->str[0] == '\0'
			&& info->cmd_lst[i].redi == NULL)
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

	if (all_is_space(line))
		return (ERROR);
	if (check_incorrect_line(line))
		return (ERROR);
	new_line = pre_processing(line, info);
	make_command(new_line, info);
	if (check_incorrect_pipe(info) == ERROR)
		return (ERROR);
	return (NORMAL);
}
