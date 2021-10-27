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
	info->cmd_str[cnt] = NULL;
}

int	get_cmd_list(t_info *info)
{
	int		cnt;
	t_lst	*cur;

	if (info->cmd_str)//릭 때문에 추가했고 한 번 명령어 실행 후 여기에 free하고 널 꼭 넣어주기
		return (NORMAL);
	cnt = 0;
	malloc_cmd_list(info, &cur);
	merror(info->cmd_str);
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
