/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Wilbur0306 <Wilbur0306@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:52:26 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/06 17:26:04 by Wilbur0306       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_in_heredoc(int fd, const char *limiter)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (!ft_strcmp(str, limiter))
			break ;
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
		free(str);
		str = 0;
	}
	close(fd);
}

int	check_heredoc_name(char **heredoc_file, t_line *heredoc_temp, int file_fd)
{
	char	c;
	char	*temp;

	c = ASCII_ZERO;
	while (heredoc_temp->line)
	{
		if (access(*heredoc_file, F_OK))
		{
			file_fd = open(*heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			write_in_heredoc(file_fd, heredoc_temp->line);
			return (file_fd);
		}
		else
		{
			if (c == '9')
				return (0);
			temp = ft_strdup("heredoc_temp");
			if (*heredoc_file)
				free(*heredoc_file);
			*heredoc_file = ft_strjoin(temp, &c);
			free(temp);
			c++;
		}
	}
	return (0);
}

int	open_heredoc_fd(t_commands *cmds)
{
	t_line	*heredoc_temp;
	char	*heredoc_file;
	int		file_fd;

	file_fd = 0;
	heredoc_temp = cmds->heredoc;
	heredoc_file = 0;
	while (heredoc_temp->flag)
	{
		heredoc_file = ft_strdup("heredoc_temp");
		file_fd = check_heredoc_name(&heredoc_file, heredoc_temp, file_fd);
		free(heredoc_temp->line);
		heredoc_temp->line = heredoc_file;
		heredoc_temp = heredoc_temp->next;
	}
	if (file_fd)
		file_fd = open(heredoc_file, O_RDONLY);
	unlink(heredoc_file);
	return (file_fd);
}

void	open_heredoc(t_commands *cmds)
{
	int			fd;

	if (cmds->heredoc->flag > 0)
	{
		fd = open_heredoc_fd(cmds);
		if (cmds->read_heredoc == HEREDOC_END)
			cmds->fds->infile = fd;
		else
			close(fd);
	}
}
