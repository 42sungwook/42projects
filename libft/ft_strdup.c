/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:38:09 by daijeong          #+#    #+#             */
/*   Updated: 2022/11/18 14:13:23 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	int		idx;
	int		len;

	len = ft_strlen(s1);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	idx = -1;
	while (++idx < len)
		result[idx] = s1[idx];
	result[len] = 0;
	return (result);
}
