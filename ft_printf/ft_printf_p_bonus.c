/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:32 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/14 14:57:08 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static size_t	p_prec(char *result, t_list *list)
{
	while (list->blank < list->precision - list->len)
	{
		write(1, '0', 1);
		list->blank++;
	}
	write(1, result + 32 - list->len, list->len);
	return (list->len + list->blank);
}

static size_t	p_minus(char *result, t_list *list)
{
	write(1, result + 32 - list->len, list->len);
	while (list->blank < list->width)
	{
		write(1, " ", 1);
		list->blank++;
	}
	return (list->len + list->blank);
}

static size_t	p_width(char *result, t_list *list)
{
	if (list->zero == 1)
	{
		while (list->blank < list->width - list->len)
		{
			write(1, "0", 1);
			list->blank++;
		}
		write(1, result + 32 - list->len, list->len);
		return (list->len + list->blank);
	}
	while (list->blank < list->width - list->len)
	{
		write(1, " ", 1);
		list->blank++;
	}
	write(1, result + 32 - list->len, list->len);
	return (list->len + list->blank);
}

size_t	printf_p(unsigned long long arr, t_list *list)
{
	char		result[32];

	if (arr == 0)
		return (printf_putchar('0'));
	while (arr > 0)
	{
		result[31 - list->len] = "0123456789abcdef"[arr % 16];
		arr = arr / 16;
		list->len++;
	}
	result[31 - list->len] = 'x';
	result[30 - list->len] = '0';
	list->len += 2;
	if (list->precision > list->len)
		return (p_prec(result, list));
	else if (list->minus == 1 && list->width > list->len)
		return (p_minus(result, list));
	else if (list->width > list->len)
		return (p_width(result, list));
	write(1, result + 32 - list->len, list->len);
	return (list->len);
}
