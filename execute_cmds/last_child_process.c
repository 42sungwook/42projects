/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:20:03 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/12 17:22:28 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	last_child_process(int sign, t_commands *cmds, t_token *token)
{
	pid_t		pid;

	close_pipe(token, sign);
	pid = fork();
	if (pid == 0)
	{
		init_signal();
		if (!cmds->cmd)
			exit(0);
		if (cmds->fds->infile == 0)
			dup2(token->pipe_fd[sign][READ_END], STDIN_FILENO);
		child_process_check_fd(cmds);
		close_pipe(token, sign);
		if (!check_builtins(cmds))
			execve(cmds->cmd[0], cmds->cmd, make_two_pointer_envp(token));
		else
			exit(execute_builtins(cmds, token));
	}
	close_pipe(token, sign);
	token->pid = pid;
}
