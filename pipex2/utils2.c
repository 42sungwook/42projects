#include "pipex.h"

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	nth_child_process2(t_arguments *args, t_list *temp, int sign)
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
	if (temp->cmd[0][0] == 0 || access(temp->cmd[0], X_OK) != 0)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
	close(args->fds->pipe1[0]);
	close(args->fds->pipe1[1]);
	close(args->fds->pipe2[0]);
	close(args->fds->pipe2[1]);
	execve(temp->cmd[0], temp->cmd, args->envp);
}
