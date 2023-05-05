/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:33 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/05 16:43:32 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

int	cmpcmp(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

// int	print_env(char **envp)
// {

// }

// int	add_env(char **envp, char *env)
// {

// }

// int	builtin_export(t_commands *cmd, char **envp)
// {
// 	if (cmd[1])
// 		return (print_env(envp));
// 	else
// 		return (add_env(envp, cmd[1]));
// }
