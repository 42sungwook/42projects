#include "push_swap.h"

void ps_push(char *c, t_list **stack_add, t_list **stack_del, t_count *count)
{
	t_list *temp;
	t_list *new;

	temp = *stack_del;
	new = ps_addlist(temp->num, temp->group, temp->idx);
	if (*stack_add)
		new->next = *stack_add;
	*stack_add = new;
	*stack_del = temp->next;
	free(temp);
	write(1, "p", 1);
	write(1, c, 1);
	write(1, "\n", 1);
	if (*c == 'a')
	{
		count->a++;
		count->b--;
	}
	else
	{
		count->a--;
		count->b++;
	}
}

void ps_rotate(char *c, t_list **stack, size_t num)
{
	t_list *temp;
	t_list *new;
	size_t i;

	i = 0;
	if ((*stack)->next == 0)
		return;
	while (i < num)
	{
		new = *stack;
		temp = *stack;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		*stack = new->next;
		new->next = 0;
		write(1, "r", 1);
		write(1, c, 1);
		write(1, "\n", 1);
		i++;
	}
}

void ps_reverse_rotate(char *c, t_list **stack, size_t num)
{
	t_list *temp;
	t_list *new;
	size_t i;

	i = 0;
	if ((*stack)->next == 0)
		return;
	while (i < num)
	{
		new = *stack;
		while (new->next)
		{
			temp = new;
			new = new->next;
		}
		temp->next = 0;
		new->next = *stack;
		*stack = new;
		write(1, "rr", 2);
		write(1, c, 1);
		write(1, "\n", 1);
		i++;
	}
}