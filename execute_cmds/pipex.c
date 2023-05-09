/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:20:10 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/09 22:43:57 by daijeong         ###   ########.fr       */
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

void	pipex(t_commands *cmds, t_token *token)
{
	pid_t		pid;
	int			sign;
	t_commands	*temp;

	pid = 0;
	sign = 0;
	temp = cmds->next;
	first_child_process(cmds, pid, token);
	if (cmds->next && cmds->next->next)
	{
		while (temp->next)
		{
			sign = nth_child_process(sign, temp, pid, token);
			temp = temp->next;
		}
	}
	if (temp)
		pid = last_child_process(sign, temp, token);
	else
	{
		close(token->pipe_fd[0][0]);
		close(token->pipe_fd[0][1]);
	}
	close_all_fds(cmds);
	wait_pids(cmds);
}
