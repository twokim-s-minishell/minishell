/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:31:23 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/03 17:41:07 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_quote_data(t_quote *data)
{
	data->squote_flag = 0;
	data->dquote_flag = 0;
	data->squote_cnt = 0;
	data->dquote_cnt = 0;
}

int	find_separator(char *line, int idx)
{
	int		squote_flag;
	int		dquote_flag;
	t_type	type;

	squote_flag = FALSE;
	dquote_flag = FALSE;
	while (line[idx])
	{
		type = check_type(line[idx]);
		if (type == SQUOTE && dquote_flag == FALSE)
			squote_flag ^= TRUE;
		else if (type == DQUOTE && squote_flag == FALSE)
			dquote_flag ^= TRUE;
		if (!squote_flag && !dquote_flag && (type == SPCE || type == PIPE
				|| is_redirection(line[idx])))
			break ;
		idx++;
	}
	return (idx);
}

static int	find_quote_idx(char *cmd, int *idx)
{
	while (cmd[*idx])
	{
		if (cmd[*idx] == '\"')
		{
			(*idx)++;
			while (cmd[*idx] != '\"' && cmd[*idx] != 0)
				(*idx)++;
			break ;
		}
		else if (cmd[*idx] == '\'')
		{
			(*idx)++;
			while (cmd[*idx] != '\'' && cmd[*idx] != 0)
				(*idx)++;
			break ;
		}
		else
			(*idx)++;
	}
	if (cmd[*idx] == '\"' || cmd[*idx] == '\'')
		return (TRUE);
	return (FALSE);
}

static char	**create_cmd_lst(char *cmd)
{
	int		i;
	int		str_cnt;
	char	**cmd_lst;

	str_cnt = 0;
	i = 0;
	while (find_quote_idx(cmd, &i))
	{
		str_cnt++;
		i++;
	}
	cmd_lst = (char **)malloc(sizeof(char *) * (str_cnt + 1));
	merror(cmd_lst);
	i = 0;
	while (i <= str_cnt)
		cmd_lst[i++] = NULL;
	return (cmd_lst);
}

char	**quote_split(char *cmd)
{
	int		i;
	int		quote_idx;
	int		pre_idx;
	char	**cmd_str;

	cmd_str = create_cmd_lst(cmd);
	i = 0;
	quote_idx = 0;
	pre_idx = 0;
	while (find_quote_idx(cmd, &quote_idx))
	{
		if ((cmd[quote_idx] == '\"' && cmd[pre_idx] != '\"')
			|| (cmd[quote_idx] == '\'' && cmd[pre_idx] != '\''))
			pre_idx--;
		cmd_str[i] = (char *)malloc(sizeof(char) * (quote_idx - pre_idx));
		merror(cmd_str[i]);
		ft_strlcpy(cmd_str[i], cmd + pre_idx + 1, quote_idx - pre_idx);
		pre_idx = ++quote_idx;
		i++;
	}
	return (cmd_str);
}
