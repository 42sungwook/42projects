/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:29 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/15 22:09:39 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_echo(t_commands *cmds)
{
	size_t	i;

	if (!ft_strncmp(cmds->cmd[1], "-n", 2))
		i = 2;
	else
		i = 1;
	while (cmds->cmd[i])
	{
		if (cmds->fds->outfile)
		{
			write(cmds->fds->outfile, cmds->cmd[i], ft_strlen(cmds->cmd[i]));
			if (cmds->cmd[i + 1])
				write(cmds->fds->outfile, " ", 1);
		}
		else
		{
			write(1, cmds->cmd[i], ft_strlen(cmds->cmd[i]));
			if (cmds->cmd[i + 1])
				write(1, " ", 1);
		}
		i++;
	}
	if (ft_strncmp(cmds->cmd[1], "-n", 2))
	{
		if (cmds->fds->outfile)
			write(cmds->fds->outfile, "\n", 1);
		else
			write(1, "\n", 1);
	}
	return (0);
}
