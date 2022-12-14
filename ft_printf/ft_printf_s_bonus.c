/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:32 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/14 14:46:35 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static size_t	s_prec(char *result, t_list *list)
{
	if (list->precision <= list->len)
	{
		while (list->blank < list->precision)
		{
			write(1, result[list->blank], 1);
			list->blank++;
		}
		return (list->blank);
	}
	while (list->blank < list->precision - list->len)
	{
		write(1, '0', 1);
		list->blank++;
	}
	write(1, result, list->len);
	return (list->len + list->blank);
}

static size_t	s_minus(char *result, t_list *list)
{
	write(1, result, list->len);
	while (list->blank < list->width - list->len)
	{
		write(1, " ", 1);
		list->blank++;
	}
	return (list->len + list->blank);
}

static size_t	s_width(char *result, t_list *list)
{
	if (list->zero == 1)
	{
		while (list->blank < list->width - list->len)
		{
			write(1, "0", 1);
			list->blank++;
		}
		write(1, result, list->len);
		return (list->len + list->blank);
	}
	while (list->blank < list->width - list->len)
	{
		write(1, " ", 1);
		list->blank++;
	}
	write(1, result, list->len);
	return (list->len + list->blank);
}

size_t	printf_s(char *str, t_list *list)
{
	char		result[7];

	if (!str)
	{
		result[0] = '(';
		result[1] = 'n';
		result[2] = 'u';
		result[3] = 'l';
		result[4] = 'l';
		result[5] = ')';
		result[6] = 0;
		str = result;
	}
	while (str[list->len])
		list->len++;
	if (list->precision)
		return (s_prec(str, list->len));
	else if (list->minus == 1 && list->width > list->len)
		return (s_minus(str, list));
	else if (list->width > list->len)
		return (s_width(str, list));
	write(1, str, list->len);
	return (list->len);
}

size_t	printf_c(char c, t_list *list)
{
	char	result[2];

	result[0] = c;
	result[1] = 0;
	return (printf_s(result, list));
}
