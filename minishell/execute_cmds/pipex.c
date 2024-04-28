/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:20:10 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/18 16:35:13 by daijeong         ###   ########.fr       */
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

void	child_process(t_commands *temp, t_token *token, int i)
{
	init_child_signal();
	if (!temp->cmd)
		exit(127);
	child_process_check_fd(temp);
	if (i != 0 && !temp->fds->infile)
		dup2(token->prev_fd, STDIN_FILENO);
	if (temp->next && !temp->fds->outfile)
		dup2(token->pipe_fd[WRITE_END], STDOUT_FILENO);
	close(token->pipe_fd[READ_END]);
	close(token->pipe_fd[WRITE_END]);
	if (!check_builtins(temp))
		execve(temp->cmd[0], temp->cmd, make_two_pointer_envp(token));
	else
		exit(execute_builtins(temp, token));
}

void	pipex(t_commands *cmds, t_token *token)
{
	t_commands	*temp;
	int			i;

	i = 0;
	token->prev_fd = 0;
	temp = cmds;
	while (temp)
	{
		pipe(token->pipe_fd);
		token->pid = fork();
		if (token->pid == 0)
			child_process(temp, token, i);
		if (token->prev_fd)
			close(token->prev_fd);
		token->prev_fd = token->pipe_fd[READ_END];
		close(token->pipe_fd[WRITE_END]);
		i++;
		temp = temp->next;
	}
	if (i)
		close(token->prev_fd);
	wait_pids(cmds, token);
}
