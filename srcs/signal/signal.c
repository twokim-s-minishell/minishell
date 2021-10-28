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
	if (signo == SIGUSR1)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	execve_sigint(int signo)
{
	if (signo == SIGINT)
	{
		kill(0, SIGUSR1);
		exit(0);//확인하기
	}
}
