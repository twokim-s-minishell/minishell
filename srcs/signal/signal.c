#include "minishell.h"

extern t_exit_code	g_exit_code;

void	main_sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_on_new_line();// 새로운 리드라인으로 이동
		rl_replace_line("", 0);//리드라인에 입력 하던내용 새롭게 변경
		rl_redisplay();//새로운 리드라인 출력
	}
}

void	pipe_input_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_exit_code.exit_code = -42;
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
		g_exit_code.exit_code = 130;
		g_exit_code.sigusr1_flag = TRUE;
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else if (signo == SIGQUIT)
	{
		g_exit_code.exit_code = 131;
		g_exit_code.sigusr1_flag = TRUE;
		ft_putendl_fd("Quit: 3", STDERR_FILENO);
	}
}

