#include "../minishell.h"

int	builtin_pwd(t_commands *cmd)
{
	char	*path;
	char	*buf;

	path = getcwd(buf, 0);
	return (write(1, path, ft_strlen(path)));
}
