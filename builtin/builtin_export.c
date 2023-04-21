#include "../minishell.h"

int	print_env(char **envp)
{

}

int	add_env(char **envp, char *env)
{

}

int	builtin_export(t_commands *cmd, char **envp)
{
	if (cmd[1])
		return (print_env(envp));
	else
		return (add_env(envp, cmd[1]));
}
