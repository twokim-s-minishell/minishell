#include "minishell.h"

int	wexitstatus(int status)
{
	return ((int)status >> 8 & (0x000000ff));
}
