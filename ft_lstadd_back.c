/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:59:38 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/16 20:56:19 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lastlst;

	if (!lst)
	{
		(**lst).next = new;
		return ;
	}
	lastlst = ft_lstlast(*lst);
	if (!new)
		(*lastlst).next = new;
	else
		(*lastlst).next = 0;
	new = lastlst;
}
