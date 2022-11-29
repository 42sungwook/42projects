/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:55:18 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/29 20:35:29 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_recursive(int n, int fd)
{
	char	c;

	if (n != 0)
	{
		c = n % 10 + '0';
		n /= 10;
		ft_recursive(n, fd);
		write(fd, &c, 1);
	}
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (n == 0)
		write(fd, "0", 1);
	else if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	ft_recursive(n, fd);
	return ;
}

void	ft_print_result(char *base, long long nbr, int digit)
{
	int			i;
	long long	nbr2;
	int			len_num;
	char		result[32];

	i = 0;
	nbr2 = nbr;
	len_num = 0;
	if (nbr == 0)
	{
		write(1, &base[0], 1);
		return ;
	}
	while (nbr / digit != 0 || nbr % digit != 0)
	{
		len_num++;
		nbr = nbr / digit;
	}
	while (nbr2 / digit != 0 || nbr2 % digit != 0)
	{
		result[len_num - 1 - i] = base[nbr2 % digit];
		nbr2 = nbr2 / digit;
		i++;
	}
	write(1, result, len_num);
}

void	ft_putnbr_base(int nbr, char *base)
{
	long long	nbr2;
	int			digit;

	digit = 16;
	nbr2 = nbr;
	if (nbr2 < 0)
	{
		write(1, "-", 1);
		nbr2 = nbr2 * -1;
	}
	ft_print_result(base, nbr2, digit);
}
