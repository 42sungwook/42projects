/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:30:08 by sungwook          #+#    #+#             */
/*   Updated: 2023/02/17 19:32:42 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	make_reverse_triangle(t_list **stack_a, t_list **stack_b, \
		t_count *count)
{
	size_t	current_idx;

	current_idx = 0;
	while (count->a != count->group4)
	{
		if (ps_check_for_group4(*stack_a, current_idx) != 0)
		{
			find_best_a_to_b(stack_a, stack_b, count, current_idx);
			current_idx++;
		}
		else
			current_idx += count->group4;
	}
}

static void	send_two_groups_to_b(t_list **stack_a, t_list **stack_b, t_count *count)
{
	t_list	*temp_a;

	temp_a = *stack_a;
	while (temp_a)
	{
		if (count->a == count->group4 + count->group2)
			break ;
		if (temp_a->group == 2)
			ps_push("b", stack_b, stack_a, count);
		else if (temp_a->group == 1 || temp_a->group == 4)
			ps_rotate("a", stack_a, 1);
		else if (temp_a->group == 3)
		{
			ps_push("b", stack_b, stack_a, count);
			ps_rotate("b", stack_b, 1);
		}
		temp_a = *stack_a;
	}
}

void	start_push_swap(t_list **stack_a, t_list **stack_b, t_count *count)
{
	send_two_groups_to_b(stack_a, stack_b, count);
	make_reverse_triangle(stack_a, stack_b, count);
	send_group3_to_a(stack_a, stack_b, count);
	send_group2_to_a(stack_a, stack_b, count);
	send_group1_to_a(stack_a, stack_b, count);
	print_stacks(*stack_a, *stack_b);
}
