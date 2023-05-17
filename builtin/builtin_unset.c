/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:35 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/17 20:35:19 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_unset_cmd(char *cmd)
{
	int	i;

	i = 0;
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	while (cmd[++i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
	}
	return (0);
}

int	builtin_unset(t_token *token, char **cmd)
{
	t_envp	*temp;
	size_t	equal_location;
	int		i;

	i = 0;
	while (cmd[++i])
	{
		temp = token->envp;
		if (check_unset_cmd(cmd[i]))
			continue ;
		while (temp)
		{
			equal_location = cmpcmp(temp->str, '=');
			if ((equal_location == ft_strlen(cmd[i]) && \
				!ft_strncmp(temp->str, cmd[i], equal_location)) || \
				(!equal_location && !ft_strcmp(temp->str, cmd[i])))
			{
				token->envp = delete_envp_list(token->envp, temp);
				break ;
			}
			temp = temp->next;
		}
	}
	return (0);
}
