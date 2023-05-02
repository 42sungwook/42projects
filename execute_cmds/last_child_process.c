/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:20:03 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/02 11:41:01 by daijeong         ###   ########.fr       */
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
		child_process_check_fd(cmds);
		if (cmds->fds->infile == 0)
			dup2(pipe_fd->pipe2[READ_END], STDIN_FILENO);
		if (cmds->fds->outfile == 0)
			dup2(cmds->fds->outfile, STDOUT_FILENO);
		close(pipe_fd->pipe2[READ_END]);
		close(pipe_fd->pipe2[WRITE_END]);
		temp = cmds;
		while (temp->next)
			temp = temp->next;
		if (!cmds->cmd)
			exit(0);
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
		child_process_check_fd(cmds);
		if (cmds->fds->infile == 0)
			dup2(pipe_fd->pipe1[READ_END], STDIN_FILENO);
		if (cmds->fds->outfile == 0)
			dup2(cmds->fds->outfile, STDOUT_FILENO);
		close(pipe_fd->pipe1[READ_END]);
		close(pipe_fd->pipe1[WRITE_END]);
		temp = cmds;
		while (temp->next)
			temp = temp->next;
		if (!cmds->cmd)
			exit(0);
		execve(temp->cmd[0], temp->cmd, envp);
	}
	close(pipe_fd->pipe1[READ_END]);
	close(pipe_fd->pipe1[WRITE_END]);
	return (pid);
}
