#include "../minishell.h"

int	builtin_echo(t_commands *cmd)
{
	return (write(1, cmd->cmd[1], ft_strlen(cmd->cmd[1])));
}
