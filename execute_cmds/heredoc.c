/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:52:26 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/15 20:28:03 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_in_heredoc(int fd, const char *limiter)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (!str || !ft_strcmp(str, limiter))
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
		free(str);
		str = 0;
	}
}

int	check_heredoc_name(char *heredoc_file, t_line *heredoc_temp, int file_fd)
{
	char	*str_temp;

	str_temp = ft_itoa((long long)heredoc_temp->line);
	while (heredoc_temp->line)
	{
		heredoc_file = ft_strjoin(heredoc_file, str_temp);
		if (access(heredoc_file, F_OK))
		{
			file_fd = open(heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (heredoc_temp->next->flag)
				unlink(heredoc_file);
			write_in_heredoc(file_fd, heredoc_temp->line);
			return (file_fd);
		}
	}
	return (0);
}

int	open_heredoc_fd(t_commands *cmds)
{
	t_line	*heredoc_temp;
	char	*heredoc_file;
	int		file_fd;
	int		status;
	pid_t	pid;
	char	*str_temp;
	char	*prev_heredoc_file;

	heredoc_temp = cmds->heredoc;
	heredoc_file = ft_strdup("/tmp/heredoc_temp#");
	pid = fork();
	if (pid == 0)
	{
		init_child_signal();
		while (heredoc_temp->flag)
		{
			file_fd = check_heredoc_name(heredoc_file, heredoc_temp, file_fd);
			close(file_fd);
			heredoc_temp = heredoc_temp->next;
		}
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 1)
		return (-1);
	while (heredoc_temp->next->flag)
		heredoc_temp = heredoc_temp->next;
	str_temp = ft_itoa((long long)heredoc_temp->line);
	prev_heredoc_file = heredoc_file;
	heredoc_file = ft_strjoin(heredoc_file, str_temp);
	free(prev_heredoc_file);
	file_fd = open(heredoc_file, O_RDONLY);
	unlink(heredoc_file);
	free(str_temp);
	free(heredoc_file);
	return (file_fd);
}

int	open_heredoc(t_commands *cmds)
{
	int			fd;

	if (cmds->heredoc->flag > 0)
	{
		fd = open_heredoc_fd(cmds);
		if (fd == -1)
			return (1);
		if (cmds->read_heredoc == HEREDOC_END)
			cmds->fds->infile = fd;
		else
			close(fd);
	}
	return (0);
}
