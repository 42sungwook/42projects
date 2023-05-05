/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:33 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/05 20:38:23 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmpcmp(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

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

int	print_envp_list(t_envp *envp)
{
	t_envp	*tmp;
	t_envp	*free_tmp;

	tmp = ft_listdup(envp);
	merge_sort(&tmp, envp_lstsize(tmp));
	free_tmp = tmp;
	while (free_tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(free_tmp->str, 1);
		ft_putstr_fd("\n", 1);
		free_tmp = free_tmp->next;
	}
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

int	builtin_export(t_token *token, char **cmd)
{
	t_envp	*envp_list;
	t_envp	*tmp_list;
	int		i;
	int 	equal_location;

	i = 0;
	envp_list = token->envp;
	if (!cmd[1] || cmd[1][0] == '#')
		return (print_envp_list(envp_list));
	while (cmd[++i])
	{
		tmp_list = envp_list;
		if (!ft_isdigit(cmd[i][0]) && ft_isalpha(cmd[i][0]) && \
			ft_strncmp(cmd[i], "_", 2))
		{
			while (tmp_list)
			{
				equal_location = cmpcmp(cmd[i], '=');
				if (equal_location && \
					!ft_strncmp(tmp_list->str, cmd[i], equal_location + 1))
				{
					printf("YEST\n");
					envp_list = delete_envp_list(envp_list, tmp_list);
					break ;
				}
				tmp_list = tmp_list->next;
			}
			add_new_envp(envp_list, cmd[i]);
		}
	}
	token->envp = envp_list;
	return (0);
}


//0. export ✅
//1. export a
//2. export a= 
//3. export a=b ✅
//4. export a=b 이미 a가 있는 경우
//5. export a=b a가 알파벳,'_', '#' 이외의 것이 들어왔을 때 -> error문만 넣으면 됨
//6. export a=b c=d
