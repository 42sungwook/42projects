/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:26:18 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/18 16:22:56 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
		return (S_ISDIR(path_stat.st_mode));
	return (0);
}

void	init_cmds_fds(t_commands *cmds)
{
	if (cmds->fds)
		free(cmds->fds);
	cmds->fds = (t_fds *)malloc(sizeof(t_fds));
	cmds->fds->infile = 0;
	cmds->fds->outfile = 0;
}

int	open_infile_list(t_commands *cmds)
{
	t_line	*temp;
	int		fd;

	fd = 0;
	temp = cmds->infile;
	while (temp && temp->flag)
	{
		if (fd > 0)
			close(cmds->fds->infile);
		fd = open(temp->line, O_RDONLY);
		if (fd == -1)
		{
			write(2, "minishell: ", 11);
			perror(temp->line);
			cmds->fds->infile = -1;
			return (1);
		}
		if (cmds->read_heredoc == INFILE_END)
			cmds->fds->infile = fd;
		temp = temp->next;
	}
	return (0);
}

int	open_outfile_list(t_commands *cmds)
{
	t_line	*temp;
	int		fd;

	temp = cmds->outfile;
	fd = 0;
	while (temp->flag)
	{
		if (fd > 0)
			close(fd);
		if (temp->flag == 1)
			fd = open(temp->line, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (temp->flag == 2)
			fd = open(temp->line, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			write(2, "minishell: ", 11);
			perror(temp->line);
			cmds->fds->outfile = -1;
			return (1);
		}
		cmds->fds->outfile = fd;
		temp = temp->next;
	}
	return (0);
}

int	save_fds_in_cmds(t_commands *cmds)
{
	t_commands	*temp;

	if (open_heredoc(cmds))
		return (1);
	temp = cmds;
	while (temp)
	{
		if (open_infile_list(temp))
		{
			temp = temp->next;
			continue ;
		}
		open_outfile_list(temp);
		temp = temp->next;
	}
	return (0);
}
