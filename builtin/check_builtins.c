/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:19:15 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/17 21:03:42 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtins(t_commands	*cmds)
{
	if (cmds->cmd && cmds->cmd[0] && (!ft_strcmp(cmds->cmd[0], "echo") || \
		!ft_strcmp(cmds->cmd[0], "cd") || \
		!ft_strcmp(cmds->cmd[0], "pwd") || \
		!ft_strcmp(cmds->cmd[0], "export") || \
		!ft_strcmp(cmds->cmd[0], "unset") || \
		!ft_strcmp(cmds->cmd[0], "env") || \
		!ft_strcmp(cmds->cmd[0], "exit")))
		return (1);
	return (0);
}

int	execute_builtins(t_commands *cmds, t_token *token)
{
	if (cmds->fds->outfile < 0)
		return (-1);
	if (!ft_strcmp(cmds->cmd[0], "echo"))
		return (builtin_echo(cmds));
	else if (!ft_strcmp(cmds->cmd[0], "cd"))
		return (builtin_cd(cmds, token));
	else if (!ft_strcmp(cmds->cmd[0], "env"))
		return (builtin_env(cmds, token));
	else if (!ft_strcmp(cmds->cmd[0], "pwd"))
		return (builtin_pwd(cmds, token));
	else if (!ft_strcmp(cmds->cmd[0], "export"))
		return (builtin_export(cmds, token, cmds->cmd));
	else if (!ft_strcmp(cmds->cmd[0], "unset"))
		return (builtin_unset(token, cmds->cmd));
	else if (!ft_strcmp(cmds->cmd[0], "exit"))
		return (builtin_exit(cmds));
	return (0);
}
