/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:59:34 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/13 22:58:54 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char	*return_dest;
	unsigned char	*return_src;
	size_t			i;

	i = 0;
	return_dest = dest;
	return_src = (unsigned char *)src;
	if (!dest && !src)
		return (0);
	if (dest >= src)
	{
		while (i < len)
		{
			return_dest[i] = return_src[i];
			i++;
		}
	}
	return (dest);
}
// if dest and src overlap, behavior is undefined. dest가 src보다 짧을때 예외처리,,?