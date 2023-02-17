#include "push_swap.h"


int	ps_check_dup(t_list *answer)
{
	t_list	*temp;
	size_t	i;

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

void	ps_uncount_group(t_list *stack_a, t_count *count)
{
	if (stack_a->group == 1)
		count->group1--;
	else if (stack_a->group == 2)
		count->group2--;
	else if (stack_a->group == 3)
		count->group3--;
}

void	print_stacks(t_list *stack_a, t_list *stack_b)
{
	t_list	*temp_a;
	t_list	*temp_b;

	temp_a = stack_a;
	temp_b = stack_b;
	while (temp_a)
	{
		printf("stack a : num:%d  group:%d  idx:%zu\n", temp_a->num, temp_a->group, temp_a->idx);
		temp_a = temp_a->next;
	}
	while (temp_b)
	{
		printf("stack b : num:%d  group:%d  idx:%zu\n", temp_b->num, temp_b->group, temp_b->idx);
		temp_b = temp_b->next;
	}
}

void ps_init_count(t_count *count)
{
	count->a = 0;
	count->b = 0;
	count->group1 = 0;
	count->group2 = 0;
	count->group3 = 0;
	count->group4 = 0;
	count->g1_start_idx = 0;
	count->g2_start_idx = 0;
	count->g3_start_idx = 0;
	count->g4_start_idx = 0;
}

int	ps_check_for_group4(t_list *stack_a, size_t current_idx)
{
	t_list	*temp;

	temp = stack_a;
	while (temp)
	{
		if (temp->idx == current_idx)
		{
			if (temp->group == 4)
				return (0);
			else
				return (1);
		}
		temp = temp->next;
	}
	return (2);
}
