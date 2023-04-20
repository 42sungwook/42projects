#include "minishell.h"

void	heredoc_pipex(int temp_fd)
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