/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:13:54 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/18 14:26:59 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	envp_lstsize(t_envp *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		count++;
		lst = lst -> next;
	}
	return (count);
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

void	envp_lstadd_back(t_envp **lst, t_envp *new)
{
	t_envp	*curr;

	curr = *lst;
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (!lst)
		return ;
	while ((*lst)->next)
		lst = &(*lst)->next;
	(*lst)->next = new;
}

t_envp	*delete_envp_list(t_envp *envp_list, t_envp *tmp_list)
{
	t_envp	*prev_list;

	if (tmp_list == envp_list)
	{
		tmp_list = tmp_list->next;
		free(envp_list->str);
		free(envp_list);
		envp_list = tmp_list;
		return (envp_list);
	}
	else
	{
		prev_list = envp_list;
		while (prev_list->next != tmp_list)
			prev_list = prev_list->next;
		prev_list->next = tmp_list->next;
		free(tmp_list->str);
		free(tmp_list);
		return (envp_list);
	}
}

t_envp	*ft_listdup(t_envp *envp)
{
	t_envp	*tmp;
	t_envp	*new;
	t_envp	*head;

	tmp = envp;
	head = 0;
	while (tmp)
	{
		new = (t_envp *)malloc(sizeof(t_envp));
		new->str = ft_strdup(tmp->str);
		new->next = 0;
		if (!head)
			head = new;
		else
			envp_lstadd_back(&head, new);
		tmp = tmp->next;
	}
	return (head);
}
