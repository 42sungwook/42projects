#include "push_swap.h"

// static void send_last_group_to_a(t_list **stack_a, t_list **stack_b)
// {
// }

// static void send_two_groups_to_a(t_list **stack_a, t_list **stack_b)
// {
// }

static void make_reverse_triangle(t_list **stack_a, t_list **stack_b, t_count *count)
{
	t_list *temp_a;

	temp_a = *stack_a;
	while (temp_a)
	{
		if (count->a == count->group4)
			break;
		if (temp_a->group == 2 && (*stack_b)->group != 2)
			ps_push("b", stack_b, stack_a, count);
		else if (temp_a->group == 2)
			find_best_a_to_b(stack_a, stack_b, count);
		temp_a = *stack_a;
	}
}

static void send_two_groups_to_b(t_list **stack_a, t_list **stack_b, t_count *count)
{
	t_list *temp_a;

	temp_a = *stack_a;
	while (temp_a)
	{
		if (count->a == count->group4 + count->group2)
			break;
		if (temp_a->group == 1)
			ps_push("b", stack_b, stack_a, count);
		else if (temp_a->group == 2 || temp_a->group == 4)
			ps_rotate("a", stack_a, 1);
		else if (temp_a->group == 3)
		{
			ps_push("b", stack_b, stack_a, count);
			ps_rotate("b", stack_b, 1);
		}
		temp_a = *stack_a;
	}
}

void start_push_swap(t_list **stack_a, t_list **stack_b, t_count *count)
{
	t_list *temp_a;
	t_list *temp_b;
	send_two_groups_to_b(stack_a, stack_b, count);
	make_reverse_triangle(stack_a, stack_b, count);
	//  send_two_groups_to_a(stack_a, stack_b);
	//  send_last_group_to_a(stack_a, stack_b);

	temp_a = *stack_a;
	temp_b = *stack_b;
	while (temp_a)
	{
		printf("stack a : %d  %d\n", temp_a->num, temp_a->group);
		temp_a = temp_a->next;
	}
	while (temp_b)
	{
		printf("stack b : %d  %d\n", temp_b->num, temp_b->group);
		temp_b = temp_b->next;
	}
}