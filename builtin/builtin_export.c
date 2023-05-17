/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:33 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/17 18:11:42 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export_message(t_commands *cmds, t_envp *free_tmp)
{
	int	equal_location;
	int	i;

	if (!cmds->fds->outfile)
		cmds->fds->outfile = 1;
	while (free_tmp)
	{
		ft_putstr_fd("declare -x ", cmds->fds->outfile);
		equal_location = cmpcmp(free_tmp->str, '=');
		if (equal_location)
		{
			i = -1;
			while (++i < equal_location + 1)
				ft_putchar_fd(free_tmp->str[i], cmds->fds->outfile);
			ft_putchar_fd('"', cmds->fds->outfile);
			ft_putstr_fd(free_tmp->str + equal_location + 1, cmds->fds->outfile);
			ft_putchar_fd('"', cmds->fds->outfile);
			ft_putchar_fd('\n', cmds->fds->outfile);
		}
		else
		{
			ft_putstr_fd(free_tmp->str, cmds->fds->outfile);
			ft_putchar_fd('\n', cmds->fds->outfile);
		}
		free_tmp = free_tmp->next;
	}
}

int	print_envp_list(t_commands *cmds, t_envp *envp)
{
	t_envp	*tmp;
	t_envp	*free_tmp;

	tmp = ft_listdup(envp);
	merge_sort(&tmp, envp_lstsize(tmp));
	free_tmp = tmp;
	print_export_message(cmds, free_tmp);
	free_tmp = tmp;
	while (free_tmp)
	{
		tmp = free_tmp->next;
		free(free_tmp->str);
		free(free_tmp);
		free_tmp = tmp;
	}
	return (0);
}

void	valid_envp_name(t_envp **envp, char *str)
{
	t_envp	*temp;
	int		equal_location;

	temp = *envp;
	equal_location = cmpcmp(str, '=');
	while (temp)
	{
		if (equal_location && \
			(!ft_strncmp(temp->str, str, equal_location + 1) || \
			(!ft_strchr(temp->str, '=') && \
			ft_strncmp(str, temp->str, ft_strlen(temp->str) + 1) == '=')))
		{
			free(temp->str);
			temp->str = ft_strdup(str);
			break ;
		}
		else if (!equal_location && \
			ft_strcmp(temp->str, str) == '=')
			break ;
		if (!temp->next)
		{
			temp->next = (t_envp *)malloc(sizeof(t_envp));
			temp->next->str = ft_strdup(str);
			temp->next->next = 0;
			break ;
		}
		temp = temp->next;
	}
}

int	builtin_export(t_commands *cmds, t_token *token, char **cmd)
{
	int		i;

	i = 0;
	if (!cmd[1] || cmd[1][0] == '#')
		return (print_envp_list(cmds, token->envp));
	while (cmd[++i])
	{
		if (cmd[i][0] == '#')
			return (0);
		else if (ft_isalpha(cmd[i][0]) || cmd[i][0] == '_')
			valid_envp_name(&token->envp, cmd[i]);
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exit_status = 1;
		}
	}
	return (0);
}
