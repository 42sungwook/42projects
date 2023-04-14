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
		dup2(args->fds->pipe1[1], STDOUT_FILENO);
		close(args->fds->infile);
		close(args->fds->pipe1[0]);
		close(args->fds->pipe1[1]);
		execve(args->cmds->cmd[0], args->cmds->cmd, args->envp);
	}
}

static int	nth_child_process(t_arguments *args, pid_t pid)
{
	t_list	*temp;
	int		sign;

	sign = 0;
	temp = args->cmds->next;
	if (!temp)
		return (sign);
	while (temp->next)
	{
		if (sign == 0)
			pipe(args->fds->pipe2);
		else
			pipe(args->fds->pipe1);
		pid = fork();
		if (pid == 0)
			nth_child_process2(args, temp, sign);
		temp = temp->next;
		if (sign == 0)
		{
			sign = 1;
			close(args->fds->pipe1[0]);
			close(args->fds->pipe1[1]);
		}
		else
		{
			sign = 0;
			close(args->fds->pipe2[0]);
			close(args->fds->pipe2[1]);
		}
	}
	return (sign);
}

static pid_t	last_child_process1(t_arguments *args)
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
		execve(temp->cmd[0], temp->cmd, args->envp);
	}
	close(args->fds->pipe2[0]);
	close(args->fds->pipe2[1]);
	return (pid);
}

static pid_t	last_child_process2(t_arguments *args)
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
		execve(temp->cmd[0], temp->cmd, args->envp);
	}
	close(args->fds->pipe1[0]);
	close(args->fds->pipe1[1]);
	return (pid);
}

void	pipex(t_arguments *args)
{
	pid_t	pid;
	int		status;
	int		temp;
	int		sign;
	int		i;

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
