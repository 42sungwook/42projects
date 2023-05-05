/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:08:21 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/05 14:53:41 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipe(t_pipe *pipe_fd, int flag)
{
	if (flag == CLOSE_PIPE1 || flag == CLOSE_BOTH)
	{
		close(pipe_fd->pipe1[READ_END]);
		close(pipe_fd->pipe1[WRITE_END]);
	}
	if (flag == CLOSE_PIPE2 || flag == CLOSE_BOTH)
	{
		close(pipe_fd->pipe2[READ_END]);
		close(pipe_fd->pipe2[WRITE_END]);
	}
}

void	close_all_fds(t_commands *cmds)
{
	t_commands	*temp;

	temp = cmds;
	while (temp)
	{
		if (temp->fds)
		{
			if (temp->fds->infile > 0)
				close(cmds->fds->infile);
			if (temp->fds->outfile > 0)
				close(cmds->fds->outfile);
		}
		temp = temp->next;
	}
}
