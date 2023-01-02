/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_deque_2_bouns.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanson <chanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:58:57 by chanson           #+#    #+#             */
/*   Updated: 2023/01/02 16:16:51 by chanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	deque_back(t_deque *deque, int x, int y)
{
	t_node	*temp;

	temp = new_node(x, y);
	deque_add_back(deque, temp);
}

t_node	*new_node_2(int x, int y, int idx)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->x = x;
	node->y = y;
	node->idx = idx;
	node->next = NULL;
	node->enemy_alive = 0;
	node->enemy_dir = 0;
	node->map = 0;
	node->way = 0;
	return (node);
}

void	delete_back_deque(t_deque *deque)
{
	t_node	*temp;
	t_node	*pre_node;

	if (!deque || deque->cnt == 0)
		return ;
	temp = deque->front;
	if (deque->cnt > 1)
	{
		while (1)
		{
			pre_node = temp;
			temp = temp->next;
			if (temp->next == NULL)
				break ;
		}
		free(temp);
		pre_node->next = NULL;
		deque->cnt--;
	}
	else if (deque->cnt == 1)
	{
		free(temp);
		deque->front = NULL;
		deque->cnt--;
	}
}
