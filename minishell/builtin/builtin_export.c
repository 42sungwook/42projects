/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:33 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/18 14:31:08 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	equal_location_ox(int equal_location, t_commands *cmds, \
t_envp *free_tmp)
{
	int	i;

	if (equal_location)
	{
		i = -1;
		while (++i < equal_location + 1)
			ft_putchar_fd(free_tmp->str[i], cmds->fds->outfile);
		ft_putchar_fd('"', cmds->fds->outfile);
		ft_putstr_fd(free_tmp->str + equal_location + 1, \
					cmds->fds->outfile);
		ft_putchar_fd('"', cmds->fds->outfile);
		ft_putchar_fd('\n', cmds->fds->outfile);
	}
	else
	{
		ft_putstr_fd(free_tmp->str, cmds->fds->outfile);
		ft_putchar_fd('\n', cmds->fds->outfile);
	}
}

void	print_export_message(t_commands *cmds, t_envp *free_tmp)
{
	int	equal_location;

	if (!cmds->fds->outfile)
		cmds->fds->outfile = 1;
	while (free_tmp)
	{
		ft_putstr_fd("declare -x ", cmds->fds->outfile);
		equal_location = cmpcmp(free_tmp->str, '=');
		equal_location_ox(equal_location, cmds, free_tmp);
		free_tmp = free_tmp->next;
	}
}

int	update_envp(int equal_location, t_envp *temp, char *str)
{
	if (equal_location && \
			(!ft_strncmp(temp->str, str, equal_location + 1) || \
			(!ft_strchr(temp->str, '=') && \
			ft_strncmp(str, temp->str, ft_strlen(temp->str) + 1) == '=')))
	{
		free(temp->str);
		temp->str = ft_strdup(str);
		return (0);
	}
	else if (!equal_location && \
		ft_strcmp(temp->str, str) == '=')
		return (0);
	if (!temp->next)
	{
		temp->next = (t_envp *)malloc(sizeof(t_envp));
		temp->next->str = ft_strdup(str);
		temp->next->next = 0;
		return (0);
	}
	return (1);
}

void	valid_envp_name(t_envp **envp, char *str)
{
	t_envp	*temp;
	int		equal_location;

	temp = *envp;
	equal_location = cmpcmp(str, '=');
	if ((equal_location && check_valid_cmd(str, "export", equal_location - 1)) \
		|| (!equal_location && check_valid_cmd(str, "export", ft_strlen(str))))
		return ;
	while (temp)
	{
		if (!update_envp(equal_location, temp, str))
			return ;
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
			return (1);
		}
	}
	return (0);
}
