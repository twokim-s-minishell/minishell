#include "minishell.h"

int	double_string_size(char **str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (ERROR);
	while (str[i] != NULL)
		i++;
	return (i);
}