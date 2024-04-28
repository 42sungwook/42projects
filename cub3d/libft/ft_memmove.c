/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:00:02 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/13 19:26:17 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*return_dest;
	unsigned char	*return_src;
	size_t			i;

	if (dest == src || len == 0)
		return (dest);
	i = -1;
	return_dest = (unsigned char *)dest;
	return_src = (unsigned char *)src;
	if (dest < src)
	{
		while (++i < len)
			return_dest[i] = return_src[i];
	}
	else
	{
		while (++i < len)
			return_dest[len - i - 1] = return_src[len - i - 1];
	}
	return (return_dest);
}
