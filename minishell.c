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

void	heredoc_pipex(int	temp_fd)
{
	char	*line;

	line = readline("heredoc> ");
	while (line)
	{
		if (!line)
			break ;
		write(temp_fd, line, ft_strlen(line));
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	close(temp_fd);
}

int main()
{
	char	*str;
	int		temp_fd;

	str = 0;
	while (1)
	{
		str = readline("minishell> : ");
		//str 파싱......
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