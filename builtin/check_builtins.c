/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:19:15 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/05 20:23:19 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtins(t_commands	*cmds)
{
	if (cmds->cmd && (!ft_strcmp(cmds->cmd[0], "echo") || \
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
	if (!ft_strcmp(cmds->cmd[0], "echo"))
		builtin_echo(cmds);
	else if (!ft_strcmp(cmds->cmd[0], "cd"))
		return (builtin_cd(cmds, token));
	else if (!ft_strcmp(cmds->cmd[0], "env"))
		builtin_env(token);
	else if (!ft_strcmp(cmds->cmd[0], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(cmds->cmd[0], "export"))
		builtin_export(token, cmds->cmd);
	else if (!ft_strcmp(cmds->cmd[0], "unset"))
		builtin_unset(token, cmds->cmd);
	// else if (!ft_strcmp(cmds->cmd[0], "exit"))
	// 	builtin_exit(cmds);
	return (0);
}
