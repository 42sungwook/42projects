/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:00:48 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/13 16:02:17 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	locate;

	i = 0;
	locate = c;
	while (i < ft_strlen(s))
	{
		if (s[i] == locate)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == locate)
		return ((char *)s + i);
	return (0);
}
