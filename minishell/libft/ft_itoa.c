/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:43:30 by daijeong          #+#    #+#             */
/*   Updated: 2022/11/15 13:51:04 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n)
{
	int			count;
	long long	num;

	count = 1;
	num = n;
	if (num < 0)
	{
		num *= -1;
		count++;
	}
	while (num > 9)
	{
		count++;
		num /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long long	num;
	int			len;
	char		*res;

	num = n;
	len = get_len(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	if (num == 0)
		res[0] = '0';
	if (num < 0)
	{
		res[0] = '-';
		num *= -1;
	}
	res[len--] = '\0';
	while (num)
	{
		res[len--] = num % 10 + '0';
		num /= 10;
	}
	return (res);
}
