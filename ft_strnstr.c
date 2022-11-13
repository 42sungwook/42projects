/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:01:38 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/13 17:02:19 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (to_find[i] == 0)
		return ((char *)str);
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] && to_find[j] && str[i + j] == \
				to_find[j] && i + j < len)
			j++;
		if (to_find[j] == 0)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}
