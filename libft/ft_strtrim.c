/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:15:28 by daijeong          #+#    #+#             */
/*   Updated: 2022/11/12 16:30:59 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		start;
	int		end;
	int		idx;

	if (!s1)
		return (0);
	if (!set)
		return ((char *) s1);
	idx = 0;
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[end] && ft_strchr(set, s1[end]) && start <= end)
		end--;
	res = malloc(end - start + 2);
	if (!res)
		return (0);
	while (start <= end)
		res[idx++] = s1[start++];
	res[idx] = '\0';
	return (res);
}
