/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:46:58 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/09 21:45:27 by daijeong         ###   ########.fr       */
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
		{
			dup2(cmds->fds->infile, STDIN_FILENO);
			close(cmds->fds->infile);
		}
		if (cmds->fds->outfile)
		{
			dup2(cmds->fds->outfile, STDOUT_FILENO);
			close(cmds->fds->outfile);
		}
	}
}

void	first_child_process(t_commands *cmds, pid_t pid, \
		t_token *token)
{
	pipe(token->pipe_fd[0]);
	pid = fork();
	if (pid == 0)
	{
		if (!cmds->cmd)
			exit(0);
		child_process_check_fd(cmds);
		if (cmds->fds->outfile == 0 && cmds->next)
			dup2(token->pipe_fd[0][WRITE_END], STDOUT_FILENO);
		if (cmds->cmd[0][0] == 0 || access(cmds->cmd[0], X_OK) != 0)
			close(STDOUT_FILENO);
		close_pipe(token, CLOSE_BOTH);
		if (!check_builtins(cmds))
			execve(cmds->cmd[0], cmds->cmd, make_two_pointer_envp(token));
		else
			exit(execute_builtins(cmds, token));
	}
}
