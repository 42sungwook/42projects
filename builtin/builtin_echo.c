/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:29 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/17 18:37:52 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_echo(t_commands *cmds)
{
	size_t	i;
	size_t	j;
	int		option;

	if (!cmds->cmd[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 1;
	option = 0;
	while (cmds->cmd[i])
	{
		j = 0;
		while (cmds->cmd[i][j])
		{
			if ((j == 0 && cmds->cmd[i][j] == '-') || \
				(j != 0 && cmds->cmd[i][j] == 'n'))
				j++;
			else
				break ;
		}
		if (cmds->cmd[i][j])
			break ;
		option = 1;
		i++;
	}
	if (!cmds->fds->outfile)
		cmds->fds->outfile = 1;
	while (cmds->cmd[i])
	{
		write(cmds->fds->outfile, cmds->cmd[i], ft_strlen(cmds->cmd[i]));
		if (cmds->cmd[i + 1])
			write(cmds->fds->outfile, " ", 1);
		i++;
	}
	if (!option)
		write(cmds->fds->outfile, "\n", 1);
	return (0);
}
