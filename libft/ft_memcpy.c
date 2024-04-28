/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:59:34 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/14 17:49:01 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char	*return_dest;
	unsigned char	*return_src;
	size_t			i;

	i = 0;
	return_dest = (unsigned char *)dest;
	return_src = (unsigned char *)src;
	if (!dest && !src)
		return (0);
	while (i < len)
	{
		return_dest[i] = return_src[i];
		i++;
	}
	return (dest);
}
