/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nth_child_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:20:04 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/12 17:22:37 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nth_child_process(int sign, t_commands *cmds, t_token *token)
{
	pid_t	pid;

	pipe(token->pipe_fd[1 - sign]);
	pid = fork();
	if (pid == 0)
	{
		init_signal();
		if (!cmds->cmd)
			exit(0);
		child_process_check_fd(cmds);
		if (cmds->fds->infile == 0)
			dup2(token->pipe_fd[sign][READ_END], STDIN_FILENO);
		if (cmds->fds->outfile == 0)
			dup2(token->pipe_fd[1 - sign][WRITE_END], STDOUT_FILENO);
		if (cmds->cmd[0][0] == 0 || access(cmds->cmd[0], X_OK) != 0)
			close(STDOUT_FILENO);
		close_pipe(token, CLOSE_BOTH);
		if (!check_builtins(cmds))
			execve(cmds->cmd[0], cmds->cmd, make_two_pointer_envp(token));
		else
			exit(execute_builtins(cmds, token));
	}
	close_pipe(token, sign);
	return (1 - sign);
}
