#include "minishell.h"

void	malloc_cmd_list(t_info *info, t_lst **cur)
{
	int		cnt;
	t_lst	*tmp;

	cnt = 0;
	*cur = info->cmd_lst[info->cmd_sequence].text;
	if (*cur != NULL)
		if (is_register_variable((*cur)->str) && (*cur)->next != NULL)
			*cur = (*cur)->next;
	tmp = *cur;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		cnt++;
	}
	info->cmd_str = (char **)malloc(sizeof(char *) * (cnt + 1));
	merror(info->cmd_str);
	info->cmd_str[cnt] = NULL;
}

void	get_cmd_list(t_info *info)
{
	int		cnt;
	t_lst	*cur;

	cnt = 0;
	malloc_cmd_list(info, &cur);
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
}
