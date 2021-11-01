/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:08:04 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/11/01 15:08:05 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_exit_code	g_exit;

void	main_sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	pipe_input_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_exit.code = -42;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		ft_putstr_fd("\x1b[1A", STDERR_FILENO);
	}
}

void	here_doc_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		exit(254);
	}
}

void	execve_handler(int signo)
{
	if (signo == SIGUSR1)
	{
		signal(SIGINT, newline_handler);
		signal(SIGQUIT, newline_handler);
	}
}

void	newline_handler(int signo)
{
	int	status;

	wait(&status);
	if (signo == SIGINT)
	{
		g_exit.code = 130;
		g_exit.sig_flag = TRUE;
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else if (signo == SIGQUIT)
	{
		g_exit.code = 131;
		g_exit.sig_flag = TRUE;
		ft_putendl_fd("Quit: 3", STDERR_FILENO);
	}
}
