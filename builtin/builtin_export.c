/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:33 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/05 21:07:54 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_new_envp(t_envp *envp, char *cmd)
{
	t_envp	*tmp;
	t_envp	*new;

	tmp = envp;
	while (tmp->next)
		tmp = tmp->next;
	new = (t_envp *)malloc(sizeof(t_envp));
	new->str = ft_strdup(cmd);
	new->next = 0;
	tmp->next = new;
}

void	print_export_message(t_envp *free_tmp)
{
	int	equal_location;
	int	i;

	while (free_tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		equal_location = cmpcmp(free_tmp->str, '=') + 1;
		i = -1;
		while (++i < equal_location)
			ft_putchar_fd(free_tmp->str[i], 1);
		ft_putchar_fd('"', 1);
		ft_putstr_fd(free_tmp->str + equal_location, 1);
		ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		free_tmp = free_tmp->next;
	}
}

int	print_envp_list(t_envp *envp)
{
	t_envp	*tmp;
	t_envp	*free_tmp;

	tmp = ft_listdup(envp);
	merge_sort(&tmp, envp_lstsize(tmp));
	free_tmp = tmp;
	print_export_message(free_tmp);
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

void	valid_envp_name(t_envp *envp, char *cmd)
{
	t_envp	*tmp_list;
	int		equal_location;

	tmp_list = envp;
	equal_location = cmpcmp(cmd, '=');
	if (!equal_location)
		return ;
	while (tmp_list)
	{
		if (equal_location && \
			!ft_strncmp(tmp_list->str, cmd, equal_location + 1))
		{
			envp = delete_envp_list(envp, tmp_list);
			break ;
		}
		tmp_list = tmp_list->next;
	}
	add_new_envp(envp, cmd);
}

int	builtin_export(t_token *token, char **cmd)
{
	t_envp	*envp_list;
	t_envp	*tmp_list;
	int		i;

	i = 0;
	envp_list = token->envp;
	if (!cmd[1] || cmd[1][0] == '#')
		return (print_envp_list(envp_list));
	while (cmd[++i])
	{
		tmp_list = envp_list;
		if (!ft_isdigit(cmd[i][0]) && ft_isalpha(cmd[i][0]) && \
			ft_strncmp(cmd[i], "_", 2))
			valid_envp_name(envp_list, cmd[i]);
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
	}
	token->envp = envp_list;
	return (0);
}
