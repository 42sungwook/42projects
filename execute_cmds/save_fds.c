/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:26:18 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/16 16:44:20 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_cmds_fds(t_commands *cmds)
{
	if (cmds->fds)
		free(cmds->fds);
	cmds->fds = (t_fds *)malloc(sizeof(t_fds));
	cmds->fds->infile = 0;
	cmds->fds->outfile = 0;
}

void	open_infile_list(t_commands *cmds)
{
	t_line	*temp;
	int		fd;
	int		error_fd;

	fd = 0;
	error_fd = 0;
	temp = cmds->infile;
	while (temp && temp->flag)
	{
		if (fd > 0)
			close(cmds->fds->infile);
		fd = open(temp->line, O_RDONLY);
		if (fd == -1)
		{
			// perror(temp->line);
			error_fd = 1;
		}
		if (cmds->read_heredoc == INFILE_END)
			cmds->fds->infile = fd;
		temp = temp->next;
	}
	if (error_fd)
		cmds->fds->infile = -1;
}

void	open_outfile_list(t_commands *cmds)
{
	t_line	*temp;
	int		fd;
	int		error_fd;

	temp = cmds->outfile;
	fd = 0;
	error_fd = 0;
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
			perror(temp->line);
			error_fd = 1;
		}
		cmds->fds->outfile = fd;
		temp = temp->next;
	}
	if (error_fd)
		cmds->fds->outfile = -1;
}

int	save_fds_in_cmds(t_commands *cmds)
{
	t_commands	*temp;

	temp = cmds;
	while (temp)
	{
		init_cmds_fds(temp);
		if (open_heredoc(temp))
			return (1);
		open_infile_list(temp);
		open_outfile_list(temp);
		temp = temp->next;
	}
	return (0);
}
