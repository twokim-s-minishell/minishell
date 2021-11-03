/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:14:29 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/03 17:40:48 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_command(char *line)
{
	int	sep_idx;
	int	sep_cnt;

	sep_idx = 0;
	sep_cnt = 0;
	sep_idx = find_separator(line, sep_idx);
	while (line[sep_idx])
	{
		while (line[sep_idx] && check_type(line[sep_idx]) != PIPE)
		{
			sep_idx++;
			sep_idx = find_separator(line, sep_idx);
		}
		if (!line[sep_idx])
			break ;
		sep_cnt++;
		sep_idx++;
		sep_idx = find_separator(line, sep_idx);
	}
	return (sep_cnt + 1);
}

static char	**create_cmd(char *line, t_info *info)
{
	char	**cmd;

	info->n_cmd = count_command(line);
	cmd = (char **)malloc(sizeof(char *) * (info->n_cmd + 1));
	merror(cmd);
	ft_memset(cmd, 0, sizeof(char *) * (info->n_cmd + 1));
	return (cmd);
}

static char	**divide_by_command(char *line, t_info *info)
{
	int		i;
	int		pre_idx;
	int		cur_idx;
	char	**cmd;

	cmd = create_cmd(line, info);
	i = -1;
	pre_idx = 0;
	cur_idx = find_separator(line, pre_idx);
	while (++i < info->n_cmd)
	{
		while (check_type(line[cur_idx]) != PIPE && line[cur_idx])
		{
			if (pre_idx != cur_idx || is_separator(line[cur_idx]))
				cur_idx++;
			cur_idx = find_separator(line, cur_idx);
		}
		cmd[i] = (char *)malloc(sizeof(char) * (cur_idx - pre_idx + 1));
		merror(cmd[i]);
		ft_strlcpy(cmd[i], line + pre_idx, cur_idx - pre_idx + 1);
		pre_idx = ++cur_idx;
	}
	free(line);
	return (cmd);
}

static void	make_command_array(char **cmd, t_info *info)
{
	int		i;
	int		j;
	char	**split_cmd;
	t_cmd	*cmd_lst;

	cmd_lst = NULL;
	cmd_lst = (t_cmd *)malloc(sizeof(t_cmd) * info->n_cmd);
	merror(cmd_lst);
	ft_memset(cmd_lst, 0, sizeof(t_cmd) * info->n_cmd);
	i = -1;
	while (++i < info->n_cmd)
	{
		split_cmd = quote_split(cmd[i]);
		j = 0;
		while (split_cmd[j] != NULL)
		{
			if (is_redirection(split_cmd[j][0]))
				link_node(split_cmd[j], &(cmd_lst[i].redi));
			else
				link_node(split_cmd[j], &(cmd_lst[i].text));
			j++;
		}
		free_double_string(split_cmd);
	}
	info->cmd_lst = cmd_lst;
}

void	make_command(char *line, t_info *info)
{
	char	**cmd;

	cmd = divide_by_command(line, info);
	make_command_array(cmd, info);
	free_double_string(cmd);
}
