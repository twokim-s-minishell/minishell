/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:29:32 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/01 15:29:32 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error(void)//얘 사용하는지?
{
	const char	*error_message;

	error_message = strerror(errno);
	ft_putendl_fd((char *)error_message, STDERR_FILENO);
	return (ERROR);
}

void	merror(void *addr)
{
	if (addr == NULL)
	{
		strerror(errno);
		exit(2);
	}
}

void	error_message(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	syntax_error(char c)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token '", STDERR_FILENO);
	if (c == '\0')
		ft_putstr_fd("newline", STDERR_FILENO);
	else
		ft_putchar_fd(c, STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
}

void	unclosed_quote(char c)
{
	ft_putstr_fd("Unclosed quote '", STDERR_FILENO);
	if (c == '\'')
		ft_putendl_fd("''", STDERR_FILENO);
	else
		ft_putendl_fd("\"'", STDERR_FILENO);
}
