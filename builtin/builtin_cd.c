/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:28 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/05 15:44:49 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(t_commands *cmds, char **envp)
{
	size_t	i;

	i = 0;
	if (cmds->cmd[1] == 0 || !ft_strcmp(cmds->cmd[1], "~"))
	{
		while (envp[i])
		{
			if (!ft_strncmp(envp[i], "HOME=", 5))
				break ;
			i++;
		}
		if (envp[i] == 0)
		{
			write(2, "cd: HOME not set\n", 17);
			return (1);
		}
		chdir(envp[i] + 5);
		return (0);
	}
	if (chdir(cmds->cmd[1]))
	{
		write(2, "minishell: cd: ", 15);
		perror(cmds->cmd[1]);
		return (1);
	}
	return (0);
}
