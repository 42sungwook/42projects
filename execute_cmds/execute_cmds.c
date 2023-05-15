/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:11:07 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/15 20:13:30 by daijeong         ###   ########.fr       */
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
	char		**envp;

	envp = make_two_pointer_envp(token);
	if (save_cmds(cmds, envp))
		return (1);
	if (check_builtins(cmds) && !cmds->next)
	{
		execute_builtins(cmds, token);
		return (0);
	}
	pipex(cmds, token);
	free_arr(envp);
	return (0);
}
