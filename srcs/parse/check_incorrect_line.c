/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_incorrect_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:09:23 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/01 19:43:07 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redirection(char *line, int *i)
{
	int		redi_cnt;
	int		j;
	t_type	type;

	redi_cnt = 1;
	j = 0;
	type = is_redirection(line[*i]);
	while (type == is_redirection(line[*i + redi_cnt]) && line[*i + redi_cnt])
		redi_cnt++;
	if (redi_cnt > 2 || is_redirection(line[*i + redi_cnt]))
	{
		if (!line[*i + redi_cnt])
			redi_cnt--;
		*i += redi_cnt;
		return (TRUE);
	}
	type = check_type(line[*i + redi_cnt + j]);
	while (type == SPCE)
		type = check_type(line[*i + redi_cnt + ++j]);
	if (line[*i + redi_cnt + j] == '\0')
	{
		*i += redi_cnt + j;
		return (TRUE);
	}
	return (FALSE);
}

static int	separator_in_a_row(char *line, int i)
{
	int	pipe_flag;

	pipe_flag = FALSE;
	if (is_separator(line[i]) && !is_space(line[i]))
	{
		if (check_type(line[i]) == PIPE)
			pipe_flag = TRUE;
		if (is_redirection(line[i++]))
			if (is_redirection(line[i]))
				i++;
		while (is_space(line[i]))
			i++;
		if (is_separator(line[i]))
		{
			if (line[i] == '\0' && pipe_flag == TRUE)
				syntax_error("|");
			else if (pipe_flag == FALSE && is_redirection(line[i]))
				syntax_error(&line[i]);
			else
				return (FALSE);
			return (TRUE);
		}
	}
	return (FALSE);
}

static int	check_incorrect_case(char *line, int i)
{
	if ((line[i] == ';' || line[i] == '\\'))
		syntax_error(&line[i]);
	else if (check_type(line[i]) == PIPE && check_type(line[i + 1]) == PIPE)
		syntax_error(&line[i]);
	else if (is_redirection(line[i]) && check_redirection(line, &i))
		syntax_error(&line[i]);
	else if (separator_in_a_row(line, i))
		return (TRUE);
	else
		return (FALSE);
	return (TRUE);
}

int	check_closed_quote(t_quote data)
{
	if (data.squote_cnt & ISODD)
		unclosed_quote('\'');
	else if (data.dquote_cnt & ISODD)
		unclosed_quote('\"');
	else
		return (FALSE);
	return (TRUE);
}

int	check_incorrect_line(char *line)
{
	int		i;
	t_quote	data;

	init_quote_data(&data);
	i = -1;
	while (line[++i])
	{
		if (check_type(line[i]) == SQUOTE && data.dquote_flag == FALSE)
		{
			data.squote_cnt++;
			data.squote_flag ^= TRUE;
		}
		else if (check_type(line[i]) == DQUOTE && data.squote_flag == FALSE)
		{
			data.dquote_cnt++;
			data.dquote_flag ^= TRUE;
		}
		else if (!data.squote_flag && !data.dquote_flag)
			if (check_incorrect_case(line, i))
				return (TRUE);
	}
	return (check_closed_quote(data));
}
