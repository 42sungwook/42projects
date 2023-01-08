#include "push_swap.h"

int ps_check_duplist(t_list *answer)
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