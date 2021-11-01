/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:19:34 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/01 16:32:19 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	choose_enclose_quote_type(char *buf, int buf_len)
{
	int	i;

	i = 0;
	while (i < buf_len)
	{
		if (buf[i++] == '\"')
			return ('\'');
	}
	return ('\"');
}

void	turn_on_quote_flag(char c, t_quote *data)
{
	if (c == '\'')
		data->squote_flag ^= TRUE;
	else
		data->dquote_flag ^= TRUE;
}
