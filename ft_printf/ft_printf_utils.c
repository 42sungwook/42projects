/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:32 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/13 21:45:19 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	printf_di(int nbr)
{
	size_t		len;
	size_t		sign;
	long long	nbr2;
	char		result[32];

	len = 0;
	sign = 0;
	nbr2 = (long long)nbr;
	if (nbr2 < 0)
	{
		sign = printf_c('-');
		nbr2 *= -1;
	}
	if (nbr2 == 0)
		return (printf_c('0'));
	while (nbr2 > 0)
	{
		result[31 - len] = nbr2 % 10 + '0';
		nbr2 = nbr2 / 10;
		len++;
	}
	write(1, result + 32 - len, len);
	if (sign)
		len++;
	return (len);
}

size_t	printf_x(unsigned int nbr, char *base)
{
	size_t			len;
	char			result[32];

	len = 0;
	if (nbr == 0)
	{
		write(1, &base[0], 1);
		return (1);
	}
	while (nbr > 0)
	{
		result[31 - len] = base[nbr % 16];
		nbr = nbr / 16;
		len++;
	}
	write(1, result + 32 - len, len);
	return (len);
}

size_t	printf_u(unsigned int nbr)
{
	size_t		len;
	char		result[32];

	len = 0;
	if (nbr == 0)
		return (printf_c('0'));
	while (nbr > 0)
	{
		result[31 - len] = nbr % 10 + '0';
		nbr = nbr / 10;
		len++;
	}
	write(1, result + 32 - len, len);
	return (len);
}

size_t	printf_p(unsigned long long arr)
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

size_t	printf_s(char *s)
{
	int	len;

	len = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[len] != 0)
	{
		write(1, &s[len], 1);
		len++;
	}
	return (len);
}

size_t	printf_c(char s)
{
	write(1, &s, 1);
	return (1);
}
