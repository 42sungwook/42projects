/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:30 by daijeong          #+#    #+#             */
/*   Updated: 2023/04/27 15:59:31 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (write(1, envp[i], ft_strlen(envp[i])) < 0)
			return (-1);
		i++;
	}
	return (0);
}
