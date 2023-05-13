/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:20:10 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/13 13:49:57 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	wait_pids(t_commands *cmds, t_token *token)
{
	t_commands	*temp;
	int			status;
	pid_t		pid;

	temp = cmds;
	while (temp)
	{
		if (temp->cmd)
		{
			pid = waitpid(-1, &status, 0);
			if (pid == token->pid)
				g_exit_status = WEXITSTATUS(status);
		}
		temp = temp->next;
	}
}

void	pipex(t_commands *cmds, t_token *token)
{
	int			sign;
	t_commands	*temp;

	token->pid = 0;
	sign = 0;
	temp = cmds->next;
	first_child_process(cmds, token);
	if (temp && temp->next)
	{
		while (temp->next)
		{
			sign = nth_child_process(sign, temp, token);
			temp = temp->next;
		}
	}
	if (temp)
		last_child_process(sign, temp, token);
	else
		close_pipe(token, CLOSE_PIPE1);
	close_all_fds(cmds);
	wait_pids(cmds, token);
}
