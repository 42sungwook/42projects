/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:29 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/16 20:43:06 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_echo(t_commands *cmds)
{
	size_t	i;

	if (!cmds->cmd[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	if (!ft_strncmp(cmds->cmd[1], "-n", 2))
		i = 2;
	else
		i = 1;
	if (!cmds->fds->outfile)
		cmds->fds->outfile = 1;
	while (cmds->cmd[i])
	{
		write(cmds->fds->outfile, cmds->cmd[i], ft_strlen(cmds->cmd[i]));
		if (cmds->cmd[i + 1])
			write(cmds->fds->outfile, " ", 1);
		i++;
	}
	if (ft_strncmp(cmds->cmd[1], "-n", 2))
		write(cmds->fds->outfile, "\n", 1);
	return (0);
}
