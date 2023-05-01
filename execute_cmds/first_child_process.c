/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:46:58 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/01 20:15:16 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process_check_fd(t_commands *cmds)
{
	if (cmds->fds->infile == -1 || cmds->fds->outfile == -1)
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

void	first_child_process(t_commands *cmds, pid_t pid, char **envp, t_pipe pipe_fd)
{
	pipe(pipe_fd.pipe1);
	pid = fork();
	if (pid == 0)
	{
		child_process_check_fd(cmds);
		if (cmds->cmd[0][0] == 0 || access(cmds->cmd[0], X_OK) != 0)
			close(STDOUT_FILENO);
		// dup2(pipe_fd.pipe1[WRITE_END], STDOUT_FILENO);
		// close(pipe_fd.pipe1[READ_END]);
		// close(pipe_fd.pipe1[WRITE_END]);
		execve(cmds->cmd[0], cmds->cmd, envp);
	}
}
