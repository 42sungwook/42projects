/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:01:40 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/16 20:07:07 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	temp = *lst;
	if (!temp)
		return ;
	while ((*temp).next)
	{
		temp = (**lst).next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	ft_lstdelone(*lst, del);
	*lst = 0;
}
