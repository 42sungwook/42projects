/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:06:17 by daijeong          #+#    #+#             */
/*   Updated: 2022/11/18 15:18:28 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	size_t			s_len;
	size_t			d_len;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	if (dstsize <= d_len)
		return (s_len + dstsize);
	while (*dst)
		dst++;
	i = 0;
	while (*src && d_len + i < dstsize - 1)
	{
		*dst++ = *src++;
		i++;
	}
	*dst = '\0';
	return (d_len + s_len);
}
