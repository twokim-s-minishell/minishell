/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:15:25 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/01 15:15:27 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_line(t_info *info)
{
	int		i;
	t_cmd	*cur;
	t_lst	*text;
	t_lst	*redi;

	i = -1;
	while (++i < info->n_cmd)
	{
		cur = &(info->cmd_lst[i]);
		text = cur->text;
		redi = cur->redi;
		printf("text : ");
		while (text)
		{
			printf("%s  ", text->str);
			text = text->next;
		}
		printf("\nredi : ");
		while (redi)
		{
			printf("%s  ", redi->str);
			redi = redi->next;
		}
		printf("\n\n");
	}


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

	if (all_is_space(line) || check_incorrect_line(line))
	{
		free(line);
		return (ERROR);
	}
	new_line = pre_processing(line, info);
	make_command(new_line, info);
	return (NORMAL);
}
