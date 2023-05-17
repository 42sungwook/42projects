/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:28 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/17 15:01:41 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_envp_str(t_token *token, char *str)
{
	t_envp	*temp;

	temp = token->envp;
	while (temp)
	{
		if (temp->str && !ft_strncmp(temp->str, str, ft_strlen(str)))
		{
			free(temp->str);
			temp->str = ft_strjoin(str, getcwd(0, 0));
			break ;
		}
		if (!temp->next && str)
		{
			temp->next = (t_envp *)malloc(sizeof(t_envp));
			temp->next->next = 0;
			temp->next->str = ft_strjoin(str, getcwd(0, 0));
		}
		temp = temp->next;
	}
}

int	change_to_home(t_envp *temp, t_token *token)
{
	while (temp)
	{
		if (!ft_strncmp(temp->str, "HOME=", 5))
			break ;
		temp = temp->next;
	}
	if (!temp)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	change_envp_str(token, "OLDPWD=");
	chdir(temp->str + 5);
	change_envp_str(token, "PWD=");
	return (0);
}

int	builtin_cd(t_commands *cmds, t_token *token)
{
	t_envp	*temp;

	temp = token->envp;
	if (cmds->cmd[1] == 0)
		return (change_to_home(temp, token));
	change_envp_str(token, "OLDPWD=");
	if (chdir(cmds->cmd[1]))
	{
		write(2, "minishell: cd: ", 15);
		perror(cmds->cmd[1]);
		return (1);
	}
	change_envp_str(token, "PWD=");
	return (0);
}
