/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:28 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/11 19:49:00 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_to_home(t_envp *temp)
{
	while (temp)
	{
		if (!ft_strncmp(temp->str, "HOME=", 5))
			break ;
		temp = temp->next;
	}
	if (!temp)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	chdir(temp->str + 5);
	return (0);
}

int	builtin_cd(t_commands *cmds, t_token *token)
{
	t_envp	*temp;

	temp = token->envp;
	if (cmds->cmd[1] == 0 || !ft_strcmp(cmds->cmd[1], "~"))
		return (change_to_home(temp));
	if (chdir(cmds->cmd[1]))
	{
		write(2, "minishell: cd: ", 15);
		perror(cmds->cmd[1]);
		return (1);
	}
	return (0);
}
