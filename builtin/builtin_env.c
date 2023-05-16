/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:30 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/16 20:42:29 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_commands *cmds, t_token *token)
{
	t_envp	*envp_list;

	envp_list = token->envp;
	if (!cmds->fds->outfile)
		cmds->fds->outfile = 1;
	while (envp_list)
	{
		if (write(cmds->fds->outfile, envp_list->str, \
			ft_strlen(envp_list->str)) < 0)
			return (-1);
		write(cmds->fds->outfile, "\n", 1);
		envp_list = envp_list->next;
	}
	return (0);
}
