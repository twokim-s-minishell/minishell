/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:12:52 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/03 18:04:52 by hyeonkki         ###   ########.fr       */
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
	syntax_error("|");
	return (TRUE);
}

static int	check_is_pipe_stdin_input(char *line)
{
	int	i;
	int	j;

	i = ft_strlen(line) - 1;
	while (i >= 0 && line[i] != '|')
		i--;
	if (i < 0)
		return (FALSE);
	j = i + 1;
	while (is_space(line[j]))
		j++;
	if (line[j] == '\0')
		return (TRUE);
	return (FALSE);
}

static char	*put_in_pipe_input(void)
{
	char	*add;

	while (TRUE)
	{
		add = readline("> ");
		if (g_exit.code == -42)
		{
			free(add);
			g_exit.code = 1;
			return (NULL);
		}
		if (add == NULL)
		{
			ft_putstr_fd("\x1b[1A", STDERR_FILENO);
			ft_putstr_fd("\033[2C", STDERR_FILENO);
			error_msg("syntax error", NULL, "unexpected end of file");
			return (NULL);
		}
		if (add[0] != '\0')
			break ;
		free(add);
	}
	return (add);
}

int	check_pipe_input(char **line)
{
	char	*add;
	char	*tmp;

	if (check_pipe(*line))
		return (ERROR);
	if (check_is_pipe_stdin_input(*line))
	{
		signal(SIGINT, pipe_input_handler);
		add = put_in_pipe_input();
		if (add == NULL)
			return (ERROR);
		tmp = *line;
		*line = ft_strjoin(tmp, add);
		merror(*line);
		free(add);
		free(tmp);
	}
	return (NORMAL);
}
