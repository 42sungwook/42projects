/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:20:03 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/05 17:40:42 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	last_child_process1(t_commands *cmds, t_token *token, t_pipe *pipe_fd)
{
	pid_t		pid;
	t_commands	*temp;

	close_pipe(pipe_fd, CLOSE_PIPE1);
	pid = fork();
	if (pid == 0)
	{
		temp = cmds;
		while (temp->next)
			temp = temp->next;
		if (!temp->cmd)
			exit(0);
		child_process_check_fd(temp);
		if (temp->fds->infile == 0)
			dup2(pipe_fd->pipe2[READ_END], STDIN_FILENO);
		close_pipe(pipe_fd, CLOSE_PIPE2);
		if (!check_builtins(cmds))
			execve(cmds->cmd[0], cmds->cmd, make_two_pointer_envp(token));
		else
			exit(execute_builtins(cmds, token));
	}
	close_pipe(pipe_fd, CLOSE_PIPE2);
	return (pid);
}

pid_t	last_child_process2(t_commands *cmds, t_token *token, t_pipe *pipe_fd)
{
	pid_t		pid;
	t_commands	*temp;

	close_pipe(pipe_fd, CLOSE_PIPE2);
	pid = fork();
	if (pid == 0)
	{
		temp = cmds;
		while (temp->next)
			temp = temp->next;
		if (!temp->cmd)
			exit(0);
		child_process_check_fd(temp);
		if (temp->fds->infile == 0)
			dup2(pipe_fd->pipe1[READ_END], STDIN_FILENO);
		close_pipe(pipe_fd, CLOSE_PIPE1);
		if (!check_builtins(cmds))
			execve(cmds->cmd[0], cmds->cmd, make_two_pointer_envp(token));
		else
			exit(execute_builtins(cmds, token));
	}
	close_pipe(pipe_fd, CLOSE_PIPE1);
	return (pid);
}
