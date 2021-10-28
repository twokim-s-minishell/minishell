#include "minishell.h"

int	input_redirection(char *infile, int fd[])
{
	fd[READ] = open(infile, O_RDWR);
	if (fd[READ] == -1)
		return (ERROR);
	return (NORMAL);
}

int	output_redirection(char *outfile, int fd[])
{
	fd[WRITE] = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd[WRITE] == -1)
		return (ERROR);
	return (NORMAL);
}

/*">>" 일 때는 open() 함수 옵션에 O_APPEND*/
int	d_output_redirection(char *outfile, int fd[])
{
	fd[WRITE] = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd[WRITE] == -1)
		return (ERROR);
	return (NORMAL);
}

int	redirection(t_info *info, int fd[])
{
	t_lst	*cur;
	int		reval;
	char	**redi;

	cur = info->cmd_lst[info->cmd_sequence].redi;
	while (cur != NULL)
	{
		redi = ft_split(cur->str, '\"');
		if (!ft_strncmp(redi[0], "<<", 2))
			reval = here_doc(info, redi[1], fd);
		else if (!ft_strncmp(redi[0], ">>", 2))
			reval = d_output_redirection(redi[1], fd);
		else if (redi[0][0] == '<')
			reval = input_redirection(redi[1], fd);
		else if (redi[0][0] == '>')
			reval = output_redirection(redi[1], fd);
		if (reval <= -1)//here_doc 상태에서 ctrl+c 받거나 open() 함수 에러났을 때 if문 들어감
		{
			if (reval == ERROR)
				error_message(redi[1], NULL, strerror(errno));
			return (ERROR);
		}
		cur = cur->next;
	}
	return (NORMAL);
}
