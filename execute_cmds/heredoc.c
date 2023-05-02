/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:52:26 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/02 17:34:44 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipex_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i] || str2[i])
		return (0);
	return (1);
}

void	write_in_heredoc(int fd, char *limiter)
{
	char	*str;

	str = readline("> ");
	while (!pipex_strcmp(str, limiter))
	{
		write(fd, str, ft_strlen(str));
		free(str);
		str = readline("> ");
	}
	free(str);
	close(fd);
}

int	open_heredoc_fd(t_commands *cmds)
{
	int		i;
	t_line	*heredoc_temp;
	char	*heredoc_file;
	int		file_fd;

	i = 0;
	file_fd = 0;
	heredoc_temp = cmds->heredoc;
	heredoc_file = ft_strdup("/tmp/heredoc_temp");
	while (heredoc_temp)
	{
		if (file_fd > 0)
		{
			// unlink(heredoc_file);
			close(file_fd);
		}
		//heredoc_file 이름 바꿔주면서 open 해주는 부분 필요
		// if (access(heredoc_file, F_OK))
		// {
			file_fd = open(heredoc_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			write_in_heredoc(file_fd, heredoc_temp->line);
		// }
		heredoc_temp = heredoc_temp->next;
	}
	file_fd = open(heredoc_file, O_RDONLY);
	if (heredoc_temp->line)
		free(heredoc_temp->line);
	heredoc_temp->line = heredoc_file;
	// unlink(heredoc_file);
	return (file_fd);
}

void	open_heredoc(t_commands *cmds)
{
	t_commands	*temp_cmds;
	int			fd;

	temp_cmds = cmds;
	while (temp_cmds)
	{
		if (temp_cmds->heredoc->flag)
			fd = open_heredoc_fd(temp_cmds);
		if (temp_cmds->read_heredoc)
			temp_cmds->fds->infile = fd;
	}
}
