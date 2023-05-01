/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:20:03 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/01 21:19:29 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	last_child_process1(t_commands *cmds, char **envp, t_pipe *pipe_fd)
{
	pid_t		pid;
	t_commands	*temp;

	close(pipe_fd->pipe1[READ_END]);
	close(pipe_fd->pipe1[WRITE_END]);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipe_fd->pipe2[READ_END], STDIN_FILENO);
		dup2(cmds->fds->outfile, STDOUT_FILENO);
		close(pipe_fd->pipe2[READ_END]);
		close(pipe_fd->pipe2[WRITE_END]);
		temp = cmds;
		while (temp->next)
			temp = temp->next;
		execve(temp->cmd[0], temp->cmd, envp);
	}
	close(pipe_fd->pipe2[READ_END]);
	close(pipe_fd->pipe2[WRITE_END]);
	return (pid);
}

pid_t	last_child_process2(t_commands *cmds, char **envp, t_pipe *pipe_fd)
{
	pid_t		pid;
	t_commands	*temp;

	close(pipe_fd->pipe2[READ_END]);
	close(pipe_fd->pipe2[WRITE_END]);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipe_fd->pipe1[READ_END], STDIN_FILENO);
		dup2(cmds->fds->outfile, STDOUT_FILENO);
		close(pipe_fd->pipe1[READ_END]);
		close(pipe_fd->pipe1[WRITE_END]);
		temp = cmds;
		while (temp->next)
			temp = temp->next;
		execve(temp->cmd[0], temp->cmd, envp);
	}
	close(pipe_fd->pipe1[READ_END]);
	close(pipe_fd->pipe1[WRITE_END]);
	return (pid);
}
