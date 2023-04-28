/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:09:16 by sungwook          #+#    #+#             */
/*   Updated: 2023/04/28 21:10:03 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

int	nth_child_process_even(pid_t pid, t_arguments *args, t_list *temp)
{
	pipe(args->fds->pipe2);
	pid = fork();
	if (pid == 0)
	{
		dup2(args->fds->pipe1[READ_END], STDIN_FILENO);
		dup2(args->fds->pipe2[WRITE_END], STDOUT_FILENO);
		if (temp->cmd[0][0] == 0 || access(temp->cmd[0], X_OK) != 0)
			close(STDOUT_FILENO);
		close(args->fds->pipe1[READ_END]);
		close(args->fds->pipe1[WRITE_END]);
		close(args->fds->pipe2[READ_END]);
		close(args->fds->pipe2[WRITE_END]);
		execve(temp->cmd[0], temp->cmd, args->envp);
	}
	close(args->fds->pipe1[READ_END]);
	close(args->fds->pipe1[WRITE_END]);
	return (1);
}

int	nth_child_process_odd(pid_t pid, t_arguments *args, t_list *temp)
{
	pipe(args->fds->pipe1);
	pid = fork();
	if (pid == 0)
	{
		dup2(args->fds->pipe2[READ_END], STDIN_FILENO);
		dup2(args->fds->pipe1[WRITE_END], STDOUT_FILENO);
		if (temp->cmd[0][0] == 0 || access(temp->cmd[0], X_OK) != 0)
			close(STDOUT_FILENO);
		close(args->fds->pipe1[READ_END]);
		close(args->fds->pipe1[WRITE_END]);
		close(args->fds->pipe2[READ_END]);
		close(args->fds->pipe2[WRITE_END]);
		execve(temp->cmd[0], temp->cmd, args->envp);
	}
	close(args->fds->pipe2[READ_END]);
	close(args->fds->pipe2[WRITE_END]);
	return (0);
}

int	check_access_and_save(t_arguments *args, char **path, int i)
{
	int		j;
	char	**cmd;

	j = -1;
	while (path[++j] && args->argv[i][0] != 0)
	{
		cmd = ft_split(args->argv[i], ' ');
		cmd[0] = join_path(path[j], cmd[0]);
		if (!access(cmd[0], X_OK))
		{
			make_cmdlist(args, cmd);
			args->cmd_count++;
			break ;
		}
		free_arr(cmd);
	}
	return (j);
}

void	save_no_path(t_arguments *args, int i)
{
	char	**cmd;

	cmd = ft_split(args->argv[i], ' ');
	if (!(args->fds->infile == -1 && i + 1 == 3))
	{
		write(2, args->argv[i], ft_strlen(args->argv[i]));
		write(2, ": command not found", 19);
		write(2, "\n", 1);
	}
	make_cmdlist(args, cmd);
	args->cmd_count++;
}
