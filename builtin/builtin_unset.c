/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:35 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/05 20:16:40 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(t_token *token, char **cmd)
{
	t_envp	*envp_list;
	t_envp	*tmp_list;
	int		i;

	i = 0;
	envp_list = token->envp;
	while (cmd[++i])
	{
		tmp_list = envp_list;
		while (tmp_list)
		{
			if (!ft_strncmp(tmp_list->str, cmd[i], ft_strlen(cmd[i])) && \
				tmp_list->str[ft_strlen(cmd[i])] == '=')
			{
				envp_list = delete_envp_list(envp_list, tmp_list);
				break ;
			}
			tmp_list = tmp_list->next;
		}
	}
	token->envp = envp_list;
	return (0);
}
