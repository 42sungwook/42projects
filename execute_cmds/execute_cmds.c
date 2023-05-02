/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:11:07 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/02 16:56:21 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**make_two_pointer_envp(t_token *token)
{
	char	**envp;
	t_envp	*temp;
	int		i;

	i = 0;
	temp = token->envp;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	temp = token->envp;
	i = 0;
	while (temp)
	{
		envp[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	envp[i] = 0;
	return (envp);
}

int	execute_cmds(t_commands *cmds, t_token *token)
{
	t_pipe		*pipe_fd;
	char		**envp;

	pipe_fd = (t_pipe *)malloc(sizeof(t_pipe));
	envp = make_two_pointer_envp(token);
	save_cmds(cmds, envp);
	pipex(cmds, envp, pipe_fd);
	if (cmds->cmd)
		free_arr(cmds->cmd);
	cmds->cmd = 0;
	free_arr(envp);
	free(pipe_fd);
	return (0);
}
