#include "minishell.h"
#include <signal.h>

extern int	g_exit_code;

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();// 새로운 리드라인으로 이동
		rl_replace_line("", 0);//리드라인에 입력 하던내용 새롭게 변경
		rl_redisplay();//새로운 리드라인 출력
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
	int	status;

	if (signo == SIGUSR1)
	{
		signal(SIGINT, execve_sigint);
		signal(SIGQUIT, execve_sigint);
		wait(&status);
		g_exit_code = status;
	}
}

void	execve_sigint(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else if (signo == SIGQUIT)
	{
		ft_putendl_fd("Quit: 3", STDERR_FILENO);
	}
}
