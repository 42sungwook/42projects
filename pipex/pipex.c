/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:20:10 by sungwook          #+#    #+#             */
/*   Updated: 2023/04/15 14:43:24 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_child_process(t_arguments *args, pid_t pid)
{
	pipe(args->fds->pipe1);
	pid = fork();
	if (pid == 0)
	{
		if (args->fds->infile != -1)
			dup2(args->fds->infile, STDIN_FILENO);
		else
			close(STDIN_FILENO);
		if (args->cmds->cmd[0][0] == 0 || access(args->cmds->cmd[0], X_OK) != 0)
			close(STDOUT_FILENO);
		dup2(args->fds->pipe1[WRITE_END], STDOUT_FILENO);
		close(args->fds->infile);
		close(args->fds->pipe1[READ_END]);
		close(args->fds->pipe1[WRITE_END]);
		execve(args->cmds->cmd[0], args->cmds->cmd, args->envp);
	}
}

static int	nth_child_process(t_arguments *args, pid_t pid)
{
	t_list	*temp;
	int		sign;

	sign = 0;
	temp = args->cmds->next;
	if (!temp || !(temp->next))
		return (sign);
	while (temp->next)
	{
		if (sign == 0)
			sign = nth_child_process_even(pid, args, temp);
		else
			sign = nth_child_process_odd(pid, args, temp);
		temp = temp->next;
	}
	return (sign);
}

static pid_t	last_child_process1(t_arguments *args)
{
	pid_t	pid;
	t_list	*temp;

	close(args->fds->pipe1[READ_END]);
	close(args->fds->pipe1[WRITE_END]);
	pid = fork();
	if (pid == 0)
	{
		dup2(args->fds->pipe2[READ_END], STDIN_FILENO);
		dup2(args->fds->outfile, STDOUT_FILENO);
		close(args->fds->pipe2[READ_END]);
		close(args->fds->pipe2[WRITE_END]);
		temp = args->cmds;
		while (temp->next)
			temp = temp->next;
		execve(temp->cmd[0], temp->cmd, args->envp);
	}
	close(args->fds->pipe2[READ_END]);
	close(args->fds->pipe2[WRITE_END]);
	return (pid);
}

static pid_t	last_child_process2(t_arguments *args)
{
	pid_t	pid;
	t_list	*temp;

	close(args->fds->pipe2[READ_END]);
	close(args->fds->pipe2[WRITE_END]);
	pid = fork();
	if (pid == 0)
	{
		dup2(args->fds->pipe1[READ_END], STDIN_FILENO);
		dup2(args->fds->outfile, STDOUT_FILENO);
		close(args->fds->pipe1[READ_END]);
		close(args->fds->pipe1[WRITE_END]);
		temp = args->cmds;
		while (temp->next)
			temp = temp->next;
		execve(temp->cmd[0], temp->cmd, args->envp);
	}
	close(args->fds->pipe1[READ_END]);
	close(args->fds->pipe1[WRITE_END]);
	return (pid);
}

void	pipex(t_arguments *args)
{
	pid_t	pid;
	int		temp;
	int		sign;
	int		i;

	pid = 0;
	first_child_process(args, pid);
	sign = nth_child_process(args, pid);
	if (sign == 1)
		pid = last_child_process1(args);
	else
		pid = last_child_process2(args);
	i = 0;
	while (i < args->cmd_count)
	{
		wait(&temp);
		i++;
	}
}
