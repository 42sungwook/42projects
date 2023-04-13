#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

t_list	*cmd_addlist(char **cmds)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	list->cmds = cmds;
	list->next = 0;
	return (list);
}

void	make_cmdlist(t_arguments *args, char **cmds)
{
	t_list	*temp;

	if (!(args->cmds))
	{
		temp = cmd_addlist(cmds);
		args->cmds = temp;
	}
	else
	{
		temp = args->cmds;
		while (temp->next)
			temp = temp->next;
		temp->next = cmd_addlist(cmds);
		temp = temp->next;
	}
}

t_arguments	*init_args(int argc, char **argv, char **envp)
{
	t_arguments	*args;

	args = (t_arguments *)malloc(sizeof(t_arguments));
	args->argc = argc;
	args->argv = argv;
	args->envp = envp;
	args->cmd_count = 0;
	args->cmds = 0;
	args->fds = 0;
	return (args);
}

char	*join_path(char *str1, char *str2)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = -1;
	j = -1;
	len = ft_strlen(str1) + ft_strlen(str2) + 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	while (str1[++i])
		str[i] = str1[i];
	str[i] = '/';
	i++;
	while (str2[++j])
		str[i + j] = str2[j];
	free(str2);
	return (str);
}
