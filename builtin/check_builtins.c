/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:19:15 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/05 11:33:00 by sungwook         ###   ########.fr       */
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

void	execute_builtins(t_commands *cmds, char **envp)
{
	// if (!ft_strcmp(cmds->cmd[0], "echo"))
	// 	builtin_echo(cmds);
	// else if (!ft_strcmp(cmds->cmd[0], "cd"))
	// 	builtin_cd(cmds);
	// else if (!ft_strcmp(cmds->cmd[0], "pwd"))
	// 	builtin_pwd();
	// else if (!ft_strcmp(cmds->cmd[0], "export"))
	// 	builtin_export(cmds);
	// else if (!ft_strcmp(cmds->cmd[0], "unset"))
	// 	builtin_unset(cmds);
	// else if (!ft_strcmp(cmds->cmd[0], "env"))
	// 	builtin_env(cmds);
	// else if (!ft_strcmp(cmds->cmd[0], "exit"))
	// 	builtin_exit(cmds);
	if (cmds || envp)
		return ;
}
