/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:32 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/19 11:53:26 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static size_t	s_prec(char *result, t_list *list)
{
	int	i;

	i = 0;
	if (list->precision <= list->len && list->precision != -1)
	{
		while (i < list->width - list->precision)
		{
			write(1, " ", 1);
			i++;
		}
		while (list->blank < list->precision)
		{
			write(1, &result[list->blank], 1);
			list->blank++;
		}
		return (list->blank + i);
	}
	while (i < list->width - list->len)
	{
		write(1, " ", 1);
		i++;
	}
	write(1, result, list->len);
	return (list->len + i);
}

static size_t	s_minus(char *result, t_list *list)
{
	if (list->precision <= list->len && list->precision != -1)
	{
		while (list->blank < list->precision)
		{
			write(1, &result[list->blank], 1);
			list->blank++;
		}
		while (list->precision < list->width)
		{
			write(1, " ", 1);
			list->blank++;
			list->precision++;
		}
		return (list->blank);
	}
	write(1, result, list->len);
	while (list->len < list->width)
	{
		write(1, " ", 1);
		list->len++;
	}
	return (list->len);
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
		list->len += 6;
	}
	while (str[list->len])
		list->len++;
	if (list->minus == 1)
		return (s_minus(str, list));
	if (list->precision > -1)
		return (s_prec(str, list));
	else if (list->width > list->len)
		return (s_width(str, list));
	write(1, str, list->len);
	return (list->len);
}

size_t	printf_c(char c, t_list *list)
{
	char	result[2];

	if (c == 0)
	{
		if (list->width > 0 && list->minus == 0)
		{
			while (list->blank < list->width)
			{
				write(1, " ", 1);
				list->blank++;
			}
			write(1, "", 1);
			return (list->blank);
		}
		write(1, "", 1);
		if (list->width > 0 && list->minus != 0)
		{
			while (list->blank < list->width)
			{
				write(1, " ", 1);
				list->blank++;
			}
			return (list->blank);
		}
		list->len++;
		if (list->precision == 0)
			list->precision = -1;
		return (printf_s(result, list));
	}
	result[0] = c;
	result[1] = 0;
	if (list->precision == 0)
		list->precision = -1;
	return (printf_s(result, list));
}
