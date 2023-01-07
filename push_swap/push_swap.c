#include "push_swap.h"

int main(int ac, char **av)
{
	int num;
	size_t i;
	t_list *answer;
	t_list *temp;

	i = 1;
	answer = 0;
	if (ac < 2)
		return (0);
	while (av[i])
	{
		num = ps_atoi(av[i]);
		if (!answer)
		{
			temp = ps_addlist(num, i);
			answer = temp;
		}
		else
		{
			temp->next = ps_addlist(num, i);
			temp = temp->next;
		}
		i++;
	}
	ps_merge_sort(&answer, i - 1);
	temp = answer;
	while (temp)
	{
		printf("final : %d\n", temp->num);
		temp = temp->next;
	}
	while (answer)
	{
		temp = answer;
		answer = answer->next;
		free(temp);
	}
	system("leaks push_swap");
}
