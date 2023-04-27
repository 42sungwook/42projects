#include "../minishell.h"

char	**add_cmd(char **cmd, char *word)
{
	int		i;
	char	**new_cmd;
	char	*str;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
			i++;
	}
	new_cmd = (char **)malloc(sizeof(char *) * (i + 2));
	if (!(new_cmd))
		return (0);
	i = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			new_cmd[i] = cmd[i];
			i++;
		}
	}
	str = ft_strdup(word);
	new_cmd[i] = str;
	new_cmd[i + 1] = 0;

	return (new_cmd);
}

void	make_command(t_commands *cmds, char *word)
{
	char	*temp;

	if (cmds->cmd){
		cmds->cmd = add_cmd(cmds->cmd, word);
	}
	else
	{
		cmds->cmd = (char **)malloc(sizeof(char *) * 2);
		temp = ft_strdup(word);
		cmds->cmd[0] = temp;
		cmds->cmd[1] = 0;
	}
}
