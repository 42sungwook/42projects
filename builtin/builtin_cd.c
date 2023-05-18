/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:28 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/18 12:43:36 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_current_dir(t_token *token)
{
	t_envp	*temp;
	char	*temp_str;

	temp = token->envp;
	while (temp)
	{
		if (temp->str)
		{
			if (!ft_strncmp(temp->str, "PWD=", 4))
				break ;
		}
		temp = temp->next;
	}
	if (!temp)
		return (0);
	temp_str = ft_strdup(temp->str + 4);
	return (temp_str);
}

void	change_envp_str(t_token *token, char *str1, char *str2)
{
	t_envp	*temp;

	temp = token->envp;
	while (temp)
	{
		if (temp->str && !ft_strncmp(temp->str, str1, ft_strlen(str1)))
		{
			free(temp->str);
			temp->str = ft_strjoin(str1, str2);
			break ;
		}
		if (!temp->next && str1)
		{
			temp->next = (t_envp *)malloc(sizeof(t_envp));
			temp->next->next = 0;
			temp->next->str = ft_strjoin(str1, str2);
		}
		temp = temp->next;
	}
}

int	change_to_home(t_token *token)
{
	t_envp	*temp;
	char	*temp_str;

	temp_str = find_current_dir(token);
	temp = token->envp;
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
	change_envp_str(token, "OLDPWD=", temp_str);
	free(temp_str);
	chdir(temp->str + 5);
	temp_str = getcwd(0, 0);
	change_envp_str(token, "PWD=", temp_str);
	free(temp_str);
	return (0);
}

int	builtin_cd(t_commands *cmds, t_token *token)
{
	char	*temp_str;

	if (cmds->cmd[1] == 0)
		return (change_to_home(token));
	temp_str = find_current_dir(token);
	change_envp_str(token, "OLDPWD=", temp_str);
	free(temp_str);
	if (chdir(cmds->cmd[1]))
	{
		write(2, "minishell: cd: ", 15);
		perror(cmds->cmd[1]);
		return (1);
	}
	temp_str = getcwd(0, 0);
	change_envp_str(token, "PWD=", temp_str);
	free(temp_str);
	return (0);
}
