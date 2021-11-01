/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:12:52 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/01 15:12:53 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_exit_code	g_exit;

static int	check_pipe(char *line)
{
	int	i;
	int	j;

	i = -1;
	while (line[++i])
		if (check_type(line[i]) == PIPE)
			break ;
	if (line[i] == '\0')
		return (FALSE);
	j = 0;
	while (j < i)
		if (!is_separator(line[j++]))
			return (FALSE);
	syntax_error('|');
	return (TRUE);
}

int	check_pipe_input(char **line)
{
	int		i;
	int		j;
	char	*add;
	char	*tmp;

	if (check_pipe(*line))
		return (ERROR);
	i = 0;
	while ((*line)[i] && (*line)[i] != '|')
		i++;
	if ((*line)[i] == '\0')
		return (NORMAL);
	j = i + 1;
	while (is_space((*line)[j]))
		j++;
	if ((*line)[j] == '\0')
	{
		signal(SIGINT, pipe_input_handler);
		while (TRUE)
		{
			add = readline("> ");
			if (g_exit.code == -42)
			{
				free(add);
				g_exit.code = 1;
				return (ERROR);
			}
			if (add == NULL)
			{
				ft_putstr_fd("\x1b[1A", STDERR_FILENO);
				ft_putstr_fd("\033[2C", STDERR_FILENO);
				error_message("syntax error", NULL, "unexpected end of file");
				return (ERROR);
			}
			if (add[0] != '\0')
				break ;
		}
		tmp = *line;
		*line = ft_strjoin(tmp, add);
		merror(*line);
		free(add);
		free(tmp);
	}
	return (NORMAL);
}
