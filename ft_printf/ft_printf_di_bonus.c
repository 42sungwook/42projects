/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_di_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:02:02 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/14 14:57:30 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static size_t	di_prec(char *result, t_list *list)
{
	if (list->sign == 1)
		write(1, "-", 1);
	while (list->blank < list->precision - list->len)
	{
		write(1, '0', 1);
		list->blank++;
	}
	write(1, result + 32 - list->len, list->len);
	return (list->len + list->sign + list->blank);
}

static size_t	di_minus(char *result, t_list *list)
{
	if (list->sign == 1)
		write(1, "-", 1);
	write(1, result + 32 - list->len, list->len);
	while (list->blank < list->width - list->len)
	{
		write(1, " ", 1);
		list->blank++;
	}
	return (list->len + list->sign + list->blank);
}

static size_t	di_width(char *result, t_list *list)
{
	if (list->zero == 1)
	{
		if (list->sign == 1)
			write(1, "-", 1);
		else if (list->plus)
			list->sign = printf_putchar('+');
		while (list->blank < list->width - list->len)
		{
			write(1, "0", 1);
			list->blank++;
		}
		write(1, result + 32 - list->len, list->len);
		return (list->len + list->sign + list->blank);
	}
	while (list->blank < list->width - list->len)
	{
		write(1, " ", 1);
		list->blank++;
	}
	if (list->sign == 1)
		write(1, "-", 1);
	write(1, result + 32 - list->len, list->len);
	return (list->len + list->sign + list->blank);
}

static size_t	di_no_conv(char *result, t_list	*list)
{
	if (list->sign == 1)
		write(1, "-", 1);
	else if (list->plus)
		list->sign = printf_putchar('+');
	else if (list->space)
		list->sign = printf_putchar(' ');
	write(1, result + 32 - list->len, list->len);
	if (list->space)
		list->len++;
	return (list->len + list->sign);
}

size_t	printf_di(int nbr, t_list *list)
{
	long long	nbr2;
	char		result[32];

	nbr2 = (long long)nbr;
	if (nbr2 < 0)
	{
		list->sign = 1;
		nbr2 *= -1;
	}
	if (nbr2 == 0)
		return (printf_putchar('0'));
	while (nbr2 > 0)
	{
		result[31 - list->len] = nbr2 % 10 + '0';
		nbr2 = nbr2 / 10;
		list->len++;
	}
	if (list->precision > list->len)
		return (di_prec(result, list));
	else if (list->minus == 1 && list->width > list->len)
		return (di_minus(result, list));
	else if (list->width > list->len)
		return (di_width(result, list));
	return (di_no_conv(result, list));
}
