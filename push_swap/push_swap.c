#include "push_swap.h"

static void find_idx_in_row(t_list *stack_a, t_count *count)
{
	size_t	row_len;
	size_t	max_row_len;
	int		num;
	t_list	*temp;

	temp = stack_a;
	max_row_len = 0;
	row_len = 0;
	while (temp)
	{
		if (temp->next != 0)
		{
			if (temp->idx + 1 == temp->next->idx)
				row_len++;
			else
			{
				if (max_row_len < row_len)
				{
					num = temp->num - row_len;
					max_row_len = row_len;
				}
				row_len = 0;
			}
		}
		temp = temp->next;
	}
	temp = stack_a;
	count->group4 = max_row_len + 1;
	if (max_row_len == 0)
		return ;
	while (temp)
	{
		if (temp->num == num)
		{
			while (max_row_len + 1)
			{
				temp->group = 4;
				temp = temp->next;
				max_row_len--;
			}
			break ;
		}
		temp = temp->next;
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
