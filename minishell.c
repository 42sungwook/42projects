#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

void	parse_line(char *str, t_commands *cmds)
{
	t_token	token;
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		if (str[i] == "\"")
		if (str[i] == "\'")
		if (str[i] == "<")
		if (str[i] == ">")
		if (str[i] == "|")
		if ((!token.quote || token.quote == "\"") && str[i] == "$")
		
		if (token.heredoc == 1)
			read_heredoc(cmds);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	int			temp_fd;
	t_commands	*cmds;

	str = 0;
	while (1)
	{
		str = readline("minishell> : ");
		parse_line(str, cmds);
		execute_cmds(cmds);
		add_history(str);
		free(str);
		if (!str)
			exit(0);
		if (str[0] == 'a')
		{
			temp_fd = open("/tmp/pipex_temp", O_RDWR | O_CREAT | O_TRUNC, 0644);
			heredoc_pipex(temp_fd);
		}
	}
}

//exit long long 범위까지 256으로 나눠서 exit값 반환