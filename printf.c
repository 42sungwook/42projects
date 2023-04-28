#include "minishell.h"

int	print_cmds(t_commands *cmd)
{
	int	i;

	i = -1;
	while (cmd->cmd[++i])
		printf("cmd[%d]: %s\n", i, cmd->cmd[i]);
	return (0);
}
