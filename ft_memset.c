/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:59:18 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/09 21:24:29 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	*return_dest;
	unsigned char	value;
	size_t			i;

	i = 0;
	value = c;
	return_dest = dest;
	while (i < len)
	{
		*return_dest++ = value;
		i++;
	}
	return (dest);
}
