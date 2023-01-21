#include "push_swap.h"

void find_best_a_to_b(t_list **stack_a, t_list **stack_b, t_count *count)
{
	t_list *temp_a;
	size_t count_ra;
	size_t count_rra;
	int sign;

	sign = 0;
	count_ra = 0;
	count_rra = 0;
	temp_a = *stack_a;
	while (temp_a)
	{
		//if (find_next_idx(*stack_b, temp_a->idx) == 1)) <- 이걸로 바꿔야함
		if (temp_a->idx == (*stack_b)->idx + 1)
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

int ps_check_dup(t_list *answer)
{
	t_list *temp;
	size_t i;

	i = 0;
	temp = answer;
	while (temp->next)
	{
		temp->idx = i;
		if (temp->num == temp->next->num)
			return (1);
		temp = temp->next;
		i++;
	}
	temp->idx = i;
	return (0);
}

void	uncount_group(t_list *stack_a, t_count *count)
{
	if (stack_a->group == 1)
		count->group1--;
	else if (stack_a->group == 2)
		count->group2--;
	else if (stack_a->group == 3)
		count->group3--;
}

void print_stacks(t_list *stack_a, t_list *stack_b)
{
	t_list *temp_a;
	t_list *temp_b;

	temp_a = stack_a;
	temp_b = stack_b;
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