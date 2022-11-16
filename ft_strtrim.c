/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:42:10 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/14 20:20:17 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcmp(char s, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*trim;

	i = 0;
	j = 0;
	len = ft_strlen(s1);
	while (s1[i] && ft_strcmp(s1[i], set) == 1)
		i++;
	while (len > 0 && ft_strcmp(s1[len - 1], set) == 1)
		len--;
	if (len == 0)
		i = 0;
	trim = (char *)malloc(sizeof(char) * (len - i + 1));
	if (!trim)
		return (0);
	while (i < len)
	{
		trim[j] = s1[i];
		i++;
		j++;
	}
	trim[j] = 0;
	return (trim);
}
