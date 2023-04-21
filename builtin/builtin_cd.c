#include "../minishell.h"

int	builtin_cd(t_commands *cmd)
{
	return (chdir(cmd->cmd[1]));
}
