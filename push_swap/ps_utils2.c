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
		if (temp_a->idx == (*stack_b)->idx + 1)
			sign = 1;
		else if (sign == 0)
			count_ra++;
		else if (sign == 1 || sign == 2)
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