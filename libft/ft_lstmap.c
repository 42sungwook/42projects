/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:03:17 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/18 20:37:58 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_reset(t_list *lst, void (*del)(void *))
{
	t_list	*temp;

	temp = lst;
	while (lst)
	{
		temp = (*lst).next;
		del((*lst).content);
		free (lst);
		lst = temp;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_start;
	t_list	*new_lst;

	if (!lst || !f || !del)
		return (0);
	new_start = (t_list *)malloc(sizeof(t_list));
	if (new_start == 0)
		return (0);
	(*new_start).content = f((*lst).content);
	lst = (*lst).next;
	new_lst = new_start;
	while (lst != 0)
	{
		(*new_lst).next = (t_list *)malloc(sizeof(t_list));
		if ((*new_lst).next == 0)
		{
			ft_reset(new_start, del);
			return (0);
		}
		new_lst = (*new_lst).next;
		(*new_lst).content = f((*lst).content);
		lst = (*lst).next;
	}
	(*new_lst).next = 0;
	return (new_start);
}
