/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:30 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/05 17:45:26 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_token *token)
{
	t_envp	*envp_list;

	envp_list = token->envp;
	while (envp_list)
	{
		if (write(1, envp_list->str, ft_strlen(envp_list->str)) < 0)
			return (-1);
		write(1, "\n", 1);
		envp_list = envp_list->next;
	}
	return (0);
}
