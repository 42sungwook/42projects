/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:03:17 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/16 20:27:56 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;

	while (lst)
	{
		new_lst = f((*lst).content);
		del((*lst).content);
		lst = (*lst).next;
		new_lst = (*new_lst).next;
		if (!lst)
			return (0);
	}
	return (lst);
}
