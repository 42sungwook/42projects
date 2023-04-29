/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:46:58 by sungwook          #+#    #+#             */
/*   Updated: 2023/04/29 15:57:45 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_child_process(t_commands *cmds, pid_t pid, char **envp, t_pipe pipe_fd)
{
	pipe(pipe_fd.pipe1);
	pid = fork();
	if (pid == 0)
	{
		// if (cmds->fds->infile != -1)
		// 	dup2(cmds->fds->infile, STDIN_FILENO);
		// else
		// 	close(STDIN_FILENO);
		if (cmds->cmd[0][0] == 0 || access(cmds->cmd[0], X_OK) != 0)
			close(STDOUT_FILENO);
		// dup2(pipe_fd.pipe1[WRITE_END], STDOUT_FILENO);
		// close(cmds->fds->infile);
		// close(pipe_fd.pipe1[READ_END]);
		// close(pipe_fd.pipe1[WRITE_END]);
		execve(cmds->cmd[0], cmds->cmd, envp);
	}
}
