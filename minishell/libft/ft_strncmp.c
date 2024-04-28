/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:19:27 by daijeong          #+#    #+#             */
/*   Updated: 2022/11/14 21:23:23 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	idx;

	idx = 0;
	while (idx < n)
	{
		if (s1[idx] == 0 && s2[idx] == 0)
			break ;
		if (s1[idx] != s2[idx])
			return ((const unsigned char)s1[idx] \
			- (const unsigned char)s2[idx]);
		idx++;
	}
	return (0);
}
