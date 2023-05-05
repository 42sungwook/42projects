/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:46:58 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/05 17:40:54 by sungwook         ###   ########.fr       */
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
		t_token *token, t_pipe *pipe_fd)
{
	pipe(pipe_fd->pipe1);
	pid = fork();
	if (pid == 0)
	{
		if (!cmds->cmd)
			exit(0);
		child_process_check_fd(cmds);
		if (cmds->fds->outfile == 0 && cmds->next)
			dup2(pipe_fd->pipe1[WRITE_END], STDOUT_FILENO);
		if (cmds->cmd[0][0] == 0 || access(cmds->cmd[0], X_OK) != 0)
			close(STDOUT_FILENO);
		close_pipe(pipe_fd, CLOSE_PIPE1);
		if (!check_builtins(cmds))
			execve(cmds->cmd[0], cmds->cmd, make_two_pointer_envp(token));
		else
			exit(execute_builtins(cmds, token));
	}
}
