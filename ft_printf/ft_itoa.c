/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:42:35 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/29 20:27:01 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_len_n(int n)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
		i++;
	}
	return (len);
}

char	*ft_negative_itoa(int n)
{
	int		i;
	int		len;
	long	long_n;
	char	*num_str;

	i = 0;
	long_n = (long)n * -1;
	len = ft_len_n(n) + 1;
	num_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!num_str)
		return (0);
	num_str[0] = '-';
	while (long_n != 0)
	{
		num_str[len - 1 - i] = long_n % 10 + '0';
		long_n /= 10;
		i++;
	}
	num_str[len] = 0;
	return (num_str);
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	char	*num_str;

	if (n < 0)
		return (ft_negative_itoa(n));
	i = 0;
	len = ft_len_n(n);
	if (n == 0)
		len = 1;
	num_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!num_str)
		return (0);
	if (n == 0)
		num_str[0] = '0';
	while (n != 0)
	{
		num_str[len - 1 - i] = n % 10 + '0';
		n /= 10;
		i++;
	}
	num_str[len] = 0;
	return (num_str);
}
