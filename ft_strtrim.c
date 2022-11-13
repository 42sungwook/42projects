/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:42:10 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/13 20:22:00 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	int		new_len;
	char	*trim;

	i = 0;
	new_len = 0;
	len = ft_strlen(s1) + 1;
	trim = (char *)malloc(sizeof(char) * len);
	if (!trim)
		return (0);
	while (i < len - 1)
	{
		if (ft_strchr(set, s1[i]) == 0)
		{
			trim[new_len] = s1[i];
			new_len++;
		}
		i++;
	}
	trim[new_len] = '\0';
	return (trim);
}
