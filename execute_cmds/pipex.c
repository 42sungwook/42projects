/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:20:10 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/05 21:11:42 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	wait_pids(t_commands *cmds)
{
	t_commands	*temp;
	int			status;

	temp = cmds;
	while (temp)
	{
		wait(&status);
		temp = temp->next;
	}
}

void	pipex(t_commands *cmds, t_token *token, t_pipe *pipe_fd)
{
	pid_t	pid;
	int		sign;

	pid = 0;
	first_child_process(cmds, pid, token, pipe_fd);
	sign = nth_child_process(cmds, pid, token, pipe_fd);
	if (cmds->next)
	{
		if (sign == 1)
			pid = last_child_process1(cmds, token, pipe_fd);
		else
			pid = last_child_process2(cmds, token, pipe_fd);
	}
	else
	{
		close(pipe_fd->pipe1[0]);
		close(pipe_fd->pipe1[1]);
	}
	close_all_fds(cmds);
	wait_pids(cmds);
}
