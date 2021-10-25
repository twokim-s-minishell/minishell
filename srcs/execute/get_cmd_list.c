#include "minishell.h"

void	malloc_cmd_list(t_info *info)
{
	int		cnt;
	t_lst	*cur;

	cnt = 0;
	cur = info->cmd_lst[info->cmd_sequence].text;
	if (is_register_variable(cur->str) && cur->next != NULL)
		cur = cur->next;
	while (cur != NULL)
	{
		cur = cur->next;
		cnt++;
	}
	info->cmd_str = (char **)malloc(sizeof(char *) * (cnt + 1));
}

int	get_cmd_list(t_info *info)
{
	int		cnt;
	t_lst	*cur;

	cnt = 0;
	malloc_cmd_list(info);
	merror(info->cmd_str);
	cur = info->cmd_lst[info->cmd_sequence].text;
	if (is_register_variable(cur->str) && cur->next != NULL)
		cur = cur->next;
	while (cur != NULL)
	{
		if (cur->str != NULL && cur->str[0] != '\0')
		{
			info->cmd_str[cnt] = ft_strdup(cur->str);
			cnt++;
		}
		cur = cur->next;
	}
	info->cmd_str[cnt] = NULL;
	if (info->cmd_str[0])
		return (NORMAL);
	return (ERROR);
}
