#include "pipex.h"

static void	first_child_process(t_arguments *args, pid_t pid)
{
	pipe(args->fds->pipe1);
	pid = fork();
	if (pid == 0)
	{
		dup2(args->fds->infile, STDIN_FILENO);
		dup2(args->fds->pipe1[1], STDOUT_FILENO);
		close(args->fds->infile);
		close(args->fds->pipe1[0]);
		close(args->fds->pipe1[1]);
		execve(args->cmds->cmds[0], args->cmds->cmds, args->envp);
	}
}

static int	nth_child_process(t_arguments *args, pid_t pid)
{
	t_list	*temp;
	int		sign;

	sign = 0;
	temp = args->cmds->next;
	pipe(args->fds->pipe2);
	if (!temp)
		return (sign);
	while (temp->next)
	{
		pid = fork();
		if (pid == 0)
		{
			if (sign == 0)
			{
				dup2(args->fds->pipe1[0], STDIN_FILENO);
				dup2(args->fds->pipe2[1], STDOUT_FILENO);
			}
			else
			{
				dup2(args->fds->pipe2[0], STDIN_FILENO);
				dup2(args->fds->pipe1[1], STDOUT_FILENO);
			}
			close(args->fds->pipe1[0]);
			close(args->fds->pipe1[1]);
			close(args->fds->pipe2[0]);
			close(args->fds->pipe2[1]);
			execve(temp->cmds[0], temp->cmds, args->envp);
		}
		temp = temp->next;
		if (sign == 0)
			sign = 1;
		else
			sign = 0;
	}
	return (sign);
}

static pid_t	last_child_process1(t_arguments *args, int sign)
{
	pid_t	pid;
	t_list	*temp;

	close(args->fds->pipe1[0]);
	close(args->fds->pipe1[1]);
	pid = fork();
	if (pid == 0)
	{
		dup2(args->fds->pipe2[0], STDIN_FILENO);
		dup2(args->fds->outfile, STDOUT_FILENO);
		close(args->fds->pipe2[0]);
		close(args->fds->pipe2[1]);
		temp = args->cmds;
		while (temp->next)
			temp = temp->next;
		execve(temp->cmds[0], temp->cmds, args->envp);
	}
	close(args->fds->pipe2[0]);
	close(args->fds->pipe2[1]);
	return (pid);
}

static pid_t	last_child_process2(t_arguments *args, int sign)
{
	pid_t	pid;
	t_list	*temp;

	close(args->fds->pipe2[0]);
	close(args->fds->pipe2[1]);
	pid = fork();
	if (pid == 0)
	{
		dup2(args->fds->pipe1[0], STDIN_FILENO);
		dup2(args->fds->outfile, STDOUT_FILENO);
		close(args->fds->pipe1[0]);
		close(args->fds->pipe1[1]);
		temp = args->cmds;
		while (temp->next)
			temp = temp->next;
		execve(temp->cmds[0], temp->cmds, args->envp);
	}
	close(args->fds->pipe1[0]);
	close(args->fds->pipe1[1]);
	return (pid);
}

int	pipex (t_arguments *args)
{
	pid_t	pid;
	int		status;
	int		temp;
	int		sign;
	int		i;

	first_child_process(args, pid);
	sign = nth_child_process(args, pid);
	if (sign == 1)
		pid = last_child_process1(args, sign);
	else
		pid = last_child_process2(args, sign);
	i = 0;
	while (i < args->cmd_count)
	{
		if (pid == wait(&temp))
			status = temp;
		i++;
	}
	return (status);
}
