/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_deque_1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanson <chanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:58:51 by chanson           #+#    #+#             */
/*   Updated: 2023/01/02 20:12:43 by chanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

t_node	*new_node(int x, int y)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->x = x;
	node->y = y;
	node->next = NULL;
	return (node);
}

t_deque	*new_deque(void)
{
	t_deque	*deque;

	deque = (t_deque *)malloc(sizeof(t_deque));
	deque->cnt = 0;
	deque->front = NULL;
	return (deque);
}

void	deque_add_back(t_deque *deque, t_node *node)
{
	t_node	*temp;

	if (deque->cnt == 0)
	{
		deque->cnt++;
		deque->front = node;
	}
	else
	{
		deque->cnt++;
		temp = deque->front;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}

int	delete_deque(t_deque *deque)
{
	t_node	*temp;

	if (!deque)
		return (0);
	if (deque->cnt == 0)
	{
		free(deque);
		return (2);
	}
	temp = deque->front;
	while (temp)
	{
		deque->front = temp->next;
		free(temp);
		temp = deque->front;
	}
	deque->cnt = 0;
	deque->front = NULL;
	free(deque);
	return (1);
}

void	delete_front_deque(t_deque *deque)
{
	t_node	*temp;

	if (!deque)
		return ;
	if (deque->cnt == 0)
		return ;
	temp = deque->front;
	if (deque->cnt == 1)
	{
		free(temp);
		deque->front = NULL;
		deque->cnt = 0;
	}
	else if (deque->cnt > 1)
	{
		deque->front = temp->next;
		free(temp);
		deque->cnt--;
	}
}
