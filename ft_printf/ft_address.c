/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_address.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:31:26 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/04 11:01:58 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_address(unsigned long long arr)
{
	int		i;
	char	address[32];

	i = 0;
	if (arr == 0)
	{
		write(1, "0x0", 3);
		return (3);
	}
	while (i < 32)
	{
		if (arr == 0)
		{
			address[31 - i - 1] = '0';
			address[31 - i] = 'x';
			break ;
		}
		address[31 - i] = "0123456789abcdef"[arr % 16];
		arr /= 16;
		i++;
	}
	write(1, address + 30 - i, i + 2);
	return (i + 2);
}
