/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrange_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:08:45 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/02 18:39:41 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**divide_by_separator(char *line, int start_idx, int sep_idx)
{
	char	**str;
	int		front_len;
	int		mid_len;
	int		back_len;

	str = (char **)malloc(sizeof(char *) * 4);
	merror(str);
	front_len = start_idx + 1;
	mid_len = sep_idx - start_idx + 1;
	back_len = ft_strlen(line) - sep_idx + 1;
	str[FRONT] = (char *)malloc(sizeof(char) * front_len);
	merror(str[FRONT]);
	str[MID] = (char *)malloc(sizeof(char) * mid_len);
	merror(str[MID]);
	str[BACK] = (char *)malloc(sizeof(char) * back_len);
	merror(str[BACK]);
	ft_strlcpy(str[FRONT], line, front_len);
	ft_strlcpy(str[MID], line + start_idx, mid_len);
	ft_strlcpy(str[BACK], line + sep_idx, back_len);
	str[3] = NULL;
	free(line);
	return (str);
}

static char	*make_buf(void)
{
	char	*buf;

	buf = (char *)malloc(sizeof(char) * BUF_SIZE);
	merror(buf);
	return (buf);
}

static char	*make_arrange_string(char *mid, char **divide, int *start_idx)
{
	char	*tmp;
	char	*new;

	tmp = ft_strjoin(divide[FRONT], mid);
	merror(tmp);
	free(mid);
	*start_idx = (int)ft_strlen(tmp);
	new = ft_strjoin(tmp, divide[BACK]);
	merror(new);
	free(tmp);
	return (new);
}

char	*arrange_quote(char *line, int *start_idx, int sep_idx, t_info *info)
{
	char	*buf;
	char	*new;
	char	**divide;

	divide = divide_by_separator(line, *start_idx, sep_idx);
	buf = make_buf();
	new = fillin_buf(buf, divide[MID], info);
	if (new == NULL)
	{
		error_msg(NULL, NULL, "String buffer size is full");
		exit(1);
	}
	new = make_arrange_string(new, divide, start_idx);
	free_double_string(divide);
	return (new);
}
