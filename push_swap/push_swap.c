#include "push_swap.h"

static void find_idx_in_row(t_list *stack_a, t_count *count)
{
	while (stack_a)
	{
		if (stack_a->next != 0)
		{
			if (stack_a->idx + 1 == stack_a->next->idx)
			{
				if (stack_a->group != 4)
				{
					uncount_group(stack_a, count);
					stack_a->group = 4;
					count->group4++;
				}
				uncount_group(stack_a->next, count);
				stack_a->next->group = 4;
				count->group4++;
			}
		}
		stack_a = stack_a->next;
	}
}

static void div_into_three(t_list *answer, t_list *stack_a, t_count *count)
{
	t_list *temp;

	while (stack_a)
	{
		temp = answer;
		while (stack_a->num != temp->num)
			temp = temp->next;
		stack_a->idx = temp->idx;
		if (stack_a->idx < (count->a / 3))
		{
			stack_a->group = 1;
			count->group1++;
		}
		else if (stack_a->idx < ((count->a / 3) * 2))
		{
			stack_a->group = 2;
			count->group2++;
		}
		else
		{
			stack_a->group = 3;
			count->group3++;
		}
		stack_a = stack_a->next;
	}
}

static size_t make_pre_list(char **av, t_list **answer)
{
	int num;
	size_t i;
	t_list *temp;

	i = 1;
	while (av[i])
	{
		num = ps_atoi(av[i]);
		if (!(*answer))
		{
			temp = ps_addlist(num, 0, 0);
			*answer = temp;
		}
		else
		{
			temp->next = ps_addlist(num, 0, 0);
			temp = temp->next;
		}
		i++;
	}
	return (i - 1);
}

int main(int ac, char **av)
{
	t_list *answer;
	t_list *stack_a;
	t_list *stack_b;
	t_count count;

	answer = 0;
	stack_a = 0;
	stack_b = 0;
	if (ac < 2)
		return (0);
	count.a = make_pre_list(av, &answer);
	count.b = 0;
	count.group1 = 0;
	count.group2 = 0;
	count.group3 = 0;
	count.group4 = 0;
	ps_merge_sort(&answer, count.a);
	if (ps_check_dup(answer))
		exit(0);
	make_pre_list(av, &stack_a);
	div_into_three(answer, stack_a, &count);
	printf("div_into_three\n");
	print_stacks(stack_a, stack_b);
	find_idx_in_row(stack_a, &count);
	printf("find_idx_in_row\n");
	print_stacks(stack_a, stack_b);

	start_push_swap(&stack_a, &stack_b, &count);
	exit(0);
}
