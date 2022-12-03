/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:41 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/01 19:40:50 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_recursive(unsigned int n)
{
	char	c;

	if (n != 0)
	{
		c = n % 10 + '0';
		n /= 10;
		ft_recursive(n);
		write(1, &c, 1);
	}
	return ;
}

int	ft_putnbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	ft_recursive(n);
	count += ft_ul_len_n(n);
	return (count);
}
