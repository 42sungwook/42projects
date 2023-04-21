#include "../minishell.h"

int	builtin_env(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (write(1, envp[i], ft_strlen(envp[i])) < 0)
			return (-1);
		i++;
	}
	return (0);
}
