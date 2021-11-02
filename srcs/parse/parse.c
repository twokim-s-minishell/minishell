/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyunkim <kyunkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:15:25 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/02 15:48:12 by kyunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	get_here_doc_count(t_info *info)
{
	t_lst	*cur;
	char	**redi;
	int		idx;
	int		reval;
	int		here_doc_cnt;

	idx = 0;
	here_doc_cnt = 0;
	while (idx < info->n_cmd)
	{
		cur = info->cmd_lst[idx].redi;
		while (cur != NULL)
		{
			redi = ft_split(cur->str, '\"');
			if (!ft_strcmp(redi[0], "<<"))
				here_doc_cnt++;
			cur = cur->next;
			free_double_string(redi);
			redi = NULL;
		}
		idx++;
	}
	return (here_doc_cnt);
}

void	init_here_doc_fd(t_info *info)
{
	int	here_doc_cnt;

	here_doc_cnt = get_here_doc_count(info);
	info->pipex.here_doc_fd = (int *)malloc(sizeof(int) * here_doc_cnt);
	merror(info->pipex.here_doc_fd);
}

int	check_here_doc(t_info *info)
{
	int		idx;
	t_lst	*cur;
	char	**redi;
	int		here_doc_cnt;

	idx = 0;
	here_doc_cnt = 0;
	init_here_doc_fd(info);
	while (idx < info->n_cmd)
	{
		cur = info->cmd_lst[idx].redi;
		while (cur != NULL)
		{
			redi = ft_split(cur->str, '\"');
			if (!ft_strcmp(redi[0], "<<"))
			{
				info->pipex.here_doc_fd[here_doc_cnt] = here_doc(info, redi[1]);
				if (info->pipex.here_doc_fd[here_doc_cnt] == ERROR)
				{
					free_double_string(redi);
					redi = NULL;
					return (TRUE);
				}
				here_doc_cnt++;
			}
			free_double_string(redi);
			redi = NULL;
			cur = cur->next;
		}
		idx++;
	}
	return (NORMAL);
}

int	parse_line(char *line, t_info *info)
{
	char	*new_line;

	if (all_is_space(line) || check_incorrect_line(line))
		return (ERROR);
	new_line = pre_processing(line, info);
	make_command(new_line, info);
	if (check_here_doc(info))
	{
		clear_info(info);
		return (ERROR);
	}
	//여기서 에러메시지 플래그 확인해서 종료
	//플래그 값을 구분해서 in a row상황 플래그면 여기서 메시지 출력
	return (NORMAL);
}
