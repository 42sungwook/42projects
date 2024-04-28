/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:01:01 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/13 16:06:13 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	locate;

	i = ft_strlen(s);
	locate = c;
	while (i > 0)
	{
		if (s[i] == locate)
			return ((char *)s + i);
		i--;
	}
	if (s[i] == locate)
		return ((char *)s + i);
	return (0);
}
