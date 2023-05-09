/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:08:21 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/09 21:42:17 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipe(t_token *token, int flag)
{
	if (flag == CLOSE_PIPE1 || flag == CLOSE_BOTH)
	{
		close(token->pipe_fd[0][READ_END]);
		close(token->pipe_fd[0][WRITE_END]);
	}
	if (flag == CLOSE_PIPE2 || flag == CLOSE_BOTH)
	{
		close(token->pipe_fd[1][READ_END]);
		close(token->pipe_fd[1][WRITE_END]);
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
