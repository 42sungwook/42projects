#include "push_swap.h"

static void div_into_three(t_list *answer, t_list *stack_a, size_t count)
{
	t_list *temp;

	while (stack_a)
	{
		temp = answer;
		while (stack_a->num != temp->num)
			temp = temp->next;
		stack_a->idx = temp->idx;
		if (stack_a->idx < (count / 3))
			stack_a->group = 1;
		else if (stack_a->idx < ((count / 3) * 2))
			stack_a->group = 2;
		else
			stack_a->group = 3;
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
			temp = ps_addlist(num);
			*answer = temp;
		}
		else
		{
			temp->next = ps_addlist(num);
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
	size_t count;

	answer = 0;
	stack_a = 0;
	if (ac < 2)
		return (0);
	count = make_pre_list(av, &answer);
	ps_merge_sort(&answer, count);
	if (ps_check_duplist(answer))
		exit(0);
	make_pre_list(av, &stack_a);
	div_into_three(answer, stack_a, count);
	// while (stack_a)
	// {
	// 	printf("num : %d\nidx : %zu\ngroup : %d\n", stack_a->num, stack_a->idx, stack_a->group);
	// 	stack_a = stack_a->next;
	// }
	exit(0);
}
