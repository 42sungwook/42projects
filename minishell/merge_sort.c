/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:30:03 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/05 20:09:33 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	partition(t_envp *list, t_envp **left, t_envp **right, size_t size)
{
	size_t	i;
	t_envp	*temp;

	i = 0;
	temp = list;
	*left = list;
	while (i + 1 < (size / 2))
	{
		temp = temp->next;
		i++;
	}
	*right = temp->next;
	temp->next = 0;
}

static t_envp	*merge(t_envp *left, t_envp *right)
{
	t_envp	*temp;

	temp = 0;
	if (left == 0)
		return (right);
	else if (right == 0)
		return (left);
	if (ft_strcmp(left->str, right->str) < 0)
	{
		temp = left;
		temp->next = merge(left->next, right);
	}
	else
	{
		temp = right;
		temp->next = merge(left, right->next);
	}
	return (temp);
}

void	merge_sort(t_envp **list, size_t size)
{
	t_envp	*left;
	t_envp	*right;
	t_envp	*temp;

	left = *list;
	right = *list;
	temp = *list;
	if (size <= 1)
		return ;
	partition(temp, &left, &right, size);
	if (size % 2 == 0)
	{
		merge_sort(&left, size / 2);
		merge_sort(&right, size / 2);
	}
	else
	{
		merge_sort(&left, size / 2);
		merge_sort(&right, (size / 2) + 1);
	}
	*list = merge(left, right);
}
