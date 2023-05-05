/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:29 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/05 15:56:08 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_echo(t_commands *cmds)
{
	size_t	i;

	i = 1;
	while (cmds->cmd[i])
	{
		write(1, cmds->cmd[i], ft_strlen(cmds->cmd[i]));
		if (cmds->cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
