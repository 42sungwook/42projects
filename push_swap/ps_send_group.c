/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_send_group.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:26:56 by sungwook          #+#    #+#             */
/*   Updated: 2023/02/17 19:33:58 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	send_group3_to_a(t_list **stack_a, t_list **stack_b, t_count *count)
{
	size_t	i;

	i = 0;
	while (i < count->group3)
	{
		ps_reverse_rotate("b", stack_b, 1);
		find_best_b_to_a(stack_a, stack_b, count, (*stack_b)->idx);
		i++;
	}
}

void	send_group2_to_a(t_list **stack_a, t_list **stack_b, t_count *count)
{
	size_t	i;

	i = 0;
	while (i < count->group2)
	{
		ps_reverse_rotate("b", stack_b, 1);
		find_best_b_to_a(stack_a, stack_b, count, (*stack_b)->idx);
		i++;
	}
}

void	send_group1_to_a(t_list **stack_a, t_list **stack_b, t_count *count)
{
	size_t	i;

	i = 1;
	if (0 < count->group1)
		find_best_b_to_a(stack_a, stack_b, count, (*stack_b)->idx);
	while (i < count->group1)
	{
		ps_push("a", stack_a, stack_b, count);
		i++;
	}
}

void	find_best_a_to_b(t_list **stack_a, t_list **stack_b, \
		t_count *count, size_t current_idx)
{
	t_list	*temp_a;
	size_t	count_ra;
	size_t	count_rra;
	int		sign;

	sign = 0;
	count_ra = 0;
	count_rra = 1;
	temp_a = *stack_a;
	while (temp_a)
	{
		if (temp_a->idx == current_idx)
			sign = 1;
		else if (sign == 0)
			count_ra++;
		else if (sign == 1)
			count_rra++;
		temp_a = temp_a->next;
	}
	if (count_ra < count_rra)
		ps_rotate("a", stack_a, count_ra);
	else
		ps_reverse_rotate("a", stack_a, count_rra);
	ps_push("b", stack_b, stack_a, count);
}

void	find_best_b_to_a(t_list **stack_a, t_list **stack_b, \
		t_count *count, size_t current_idx)
{
	t_list	*temp_a;
	size_t	count_ra;
	size_t	count_rra;
	size_t	temp_next;
	int		sign;

	sign = 0;
	count_ra = 0;
	count_rra = 1;
	temp_next = count->group1 + count->group2 + count->group3 \
		+ count->group4 + 1;
	temp_a = *stack_a;
	while (temp_a)
	{
		if (current_idx < temp_a->idx && temp_next > temp_a->idx)
			temp_next = temp_a->idx;
		temp_a = temp_a->next;
	}
	temp_a = *stack_a;
	while (temp_a)
	{
		if (temp_a->idx == temp_next)
			sign = 1;
		else if (sign == 0)
			count_ra++;
		else if (sign == 1)
			count_rra++;
		temp_a = temp_a->next;
	}
	if (count_ra < count_rra)
		ps_rotate("a", stack_a, count_ra);
	else
		ps_reverse_rotate("a", stack_a, count_rra);
	ps_push("a", stack_a, stack_b, count);
}
