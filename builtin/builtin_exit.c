/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    .c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:31 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/16 13:18:00 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_exit(t_commands *cmds)
{
	int		i;
	int		status;
	char	*str;

	i = 0;
	status = 0;
	if (cmds->cmd[1] && cmds->cmd[2])
	{
		str = cmds->cmd[1];
		while (str[i])
		{
			if (!ft_isdigit(str[i++]))
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(str, 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(255);
			}
		}
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (cmds->cmd[1])
	{
		str = cmds->cmd[1];
		while (str[i])
		{
			if (!ft_isdigit(str[i++]))
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(str, 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(255);
			}
		}
		status = ft_atoi(str);
		ft_putstr_fd("exit\n", 2);
		exit(status);
	}
	ft_putstr_fd("exit\n", 2);
	exit(status);
	return (0);
}
