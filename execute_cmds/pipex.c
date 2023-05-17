/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:20:10 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/17 21:13:26 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	wait_pids(t_commands *cmds, t_token *token)
{
	t_commands	*temp;
	int			status;
	pid_t		pid;

	temp = cmds;
	while (temp)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == token->pid)
		{
			if (WIFSIGNALED(status))
				g_exit_status = 128 + status;
			else
				g_exit_status = WEXITSTATUS(status);
		}
		temp = temp->next;
	}
}

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

void	pipex(t_commands *cmds, t_token *token)
{
	t_commands	*temp;
	int			i;
	int			pipe_fd[2];
	int			prev_fd;

	i = 0;
	temp = cmds;
	prev_fd = 0;
	while (temp)
	{
		pipe(pipe_fd);
		token->pid = fork();
		if (token->pid == 0)
		{
			init_child_signal();
			if (!temp->cmd)
				exit(127);
			child_process_check_fd(temp);
			if (i != 0 && !temp->fds->infile)
				dup2(prev_fd, STDIN_FILENO);
			if (temp->next && !temp->fds->outfile)
				dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
			close(pipe_fd[READ_END]);
			close(pipe_fd[WRITE_END]);
			if (!check_builtins(temp))
				execve(temp->cmd[0], temp->cmd, make_two_pointer_envp(token));
			else
				exit(execute_builtins(temp, token));
		}
		if (prev_fd)
			close(prev_fd);
		prev_fd = pipe_fd[READ_END];
		close(pipe_fd[WRITE_END]);
		i++;
		temp = temp->next;
	}
	if (i)
		close(prev_fd);
	wait_pids(cmds, token);
}
