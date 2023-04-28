#include "minishell.h"

int	print_cmds(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		printf("str[%d]: %s\n", i, str[i]);
	return (0);
}
