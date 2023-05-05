/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nth_child_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:20:04 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/05 11:16:13 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	nth_child_process_even(pid_t pid, t_commands *cmds, \
			char **envp, t_pipe *pipe_fd)
{
	pipe(pipe_fd->pipe2);
	pid = fork();
	if (pid == 0)
	{
		if (!cmds->cmd)
			exit(0);
		child_process_check_fd(cmds);
		if (cmds->fds->infile == 0)
			dup2(pipe_fd->pipe1[READ_END], STDIN_FILENO);
		if (cmds->fds->outfile == 0)
			dup2(pipe_fd->pipe2[WRITE_END], STDOUT_FILENO);
		if (cmds->cmd[0][0] == 0 || access(cmds->cmd[0], X_OK) != 0)
			close(STDOUT_FILENO);
		close_pipe(pipe_fd, CLOSE_BOTH);
		if (!check_builtins(cmds))
			execve(cmds->cmd[0], cmds->cmd, envp);
		else
			execute_builtins(cmds, envp);
	}
	close_pipe(pipe_fd, CLOSE_PIPE1);
	return (1);
}

static int	nth_child_process_odd(pid_t pid, t_commands *cmds, \
			char **envp, t_pipe *pipe_fd)
{
	pipe(pipe_fd->pipe1);
	pid = fork();
	if (pid == 0)
	{
		if (!cmds->cmd)
			exit(0);
		child_process_check_fd(cmds);
		if (cmds->fds->infile == 0)
			dup2(pipe_fd->pipe2[READ_END], STDIN_FILENO);
		if (cmds->fds->outfile == 0)
			dup2(pipe_fd->pipe1[WRITE_END], STDOUT_FILENO);
		if (cmds->cmd[0][0] == 0 || access(cmds->cmd[0], X_OK) != 0)
			close(STDOUT_FILENO);
		close_pipe(pipe_fd, CLOSE_BOTH);
		if (!check_builtins(cmds))
			execve(cmds->cmd[0], cmds->cmd, envp);
		else
			execute_builtins(cmds, envp);
	}
	close_pipe(pipe_fd, CLOSE_PIPE2);
	return (0);
}

int	nth_child_process(t_commands *cmds, pid_t pid, char **envp, t_pipe *pipe_fd)
{
	t_commands	*temp;
	int			sign;

	sign = 0;
	temp = cmds->next;
	if (!temp || !(temp->next))
		return (sign);
	while (temp->next)
	{
		if (sign == 0)
			sign = nth_child_process_even(pid, temp, envp, pipe_fd);
		else
			sign = nth_child_process_odd(pid, temp, envp, pipe_fd);
		temp = temp->next;
	}
	return (sign);
}
