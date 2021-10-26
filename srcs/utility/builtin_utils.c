#include "minishell.h"

int	ft_absol(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

int	check_sign(t_ll num)
{
	if (num >= 0)
		return (1);
	return (-1);
}