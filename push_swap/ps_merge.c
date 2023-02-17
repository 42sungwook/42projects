/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_merge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:30:03 by sungwook          #+#    #+#             */
/*   Updated: 2023/02/17 19:34:06 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	partition(t_list *list, t_list **left, t_list **right, size_t size)
{
	size_t	i;
	t_list	*temp;

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

static t_list	*ps_merge(t_list *left, t_list *right)
{
	t_list	*temp;

	temp = 0;
	if (left == 0)
		return (right);
	else if (right == 0)
		return (left);
	if (left->num < right->num)
	{
		temp = left;
		temp->next = ps_merge(left->next, right);
	}
	else
	{
		temp = right;
		temp->next = ps_merge(left, right->next);
	}
	return (temp);
}

void ps_merge_sort(t_list **list, size_t size)
{
	t_list *left;
	t_list *right;
	t_list *temp;

	left = *list;
	right = *list;
	temp = *list;
	if (size <= 1)
		return ;
	partition(temp, &left, &right, size);
	if (size % 2 == 0)
	{
		ps_merge_sort(&left, size / 2);
		ps_merge_sort(&right, size / 2);
	}
	else
	{
		ps_merge_sort(&left, size / 2);
		ps_merge_sort(&right, (size / 2) + 1);
	}

	*list = ps_merge(left, right);
}
