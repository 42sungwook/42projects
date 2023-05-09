/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:20:03 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/09 21:43:37 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	last_child_process(int sign, t_commands *cmds, t_token *token)
{
	pid_t		pid;
	t_commands	*temp;

	close_pipe(token, sign);
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
			dup2(token->pipe_fd[sign][READ_END], STDIN_FILENO);
		close_pipe(token, sign);
		if (!check_builtins(temp))
			execve(temp->cmd[0], temp->cmd, make_two_pointer_envp(token));
		else
			exit(execute_builtins(temp, token));
	}
	close_pipe(token, sign);
	return (pid);
}
