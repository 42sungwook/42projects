/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:46:58 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/15 21:41:28 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process_check_fd(t_commands *cmds)
{
	if (cmds->fds->infile < 0 || cmds->fds->outfile < 0)
		exit(1);
	else
	{
		if (cmds->fds->infile)
			dup2(cmds->fds->infile, STDIN_FILENO);
		if (cmds->fds->outfile)
			dup2(cmds->fds->outfile, STDOUT_FILENO);
	}
}

void	first_child_process(t_commands *cmds, t_token *token)
{
	pid_t	pid;

	pipe(token->pipe_fd[0]);
	pipe(token->pipe_fd[1]);
	if (cmds->cmd)
	{
		pid = fork();
		if (pid == 0)
		{
			init_child_signal();
			if (!cmds->cmd)
				exit(0);
			if (cmds->fds->outfile == 0 && cmds->next)
				dup2(token->pipe_fd[0][WRITE_END], STDOUT_FILENO);
			child_process_check_fd(cmds);
			close_pipe(token, CLOSE_BOTH);
			if (!check_builtins(cmds))
				execve(cmds->cmd[0], cmds->cmd, make_two_pointer_envp(token));
			else
				exit(execute_builtins(cmds, token));
		}
		token->pid = pid;
	}
}
