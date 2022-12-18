/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:32 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/14 15:32:49 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static size_t	x_prec(char *result, t_list *list)
{
	while (list->blank < list->precision - list->len)
	{
		write(1, "0", 1);
		list->blank++;
	}
	write(1, result + 32 - list->len, list->len);
	return (list->len + list->blank);
}

static size_t	x_minus(char *result, t_list *list)
{
	write(1, result + 32 - list->len, list->len);
	while (list->blank < list->width - list->len)
	{
		write(1, " ", 1);
		list->blank++;
	}
	return (list->len + list->blank);
}

static size_t	x_width(char *result, t_list *list)
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

static char	*x_hash(char *base, char *result, t_list **list)
{
	if (base[10] == 'a')
		result[31 - (*list)->len] = 'x';
	else
		result[31 - (*list)->len] = 'X';
	result[30 - (*list)->len] = '0';
	(*list)->len += 2;
	return (result);
}

size_t	printf_x(unsigned int nbr, char *base, t_list *list)
{
	char		result[32];

	if (nbr == 0)
	{
		result[31] = '0';
		list->len++;
	}
	while (nbr > 0)
	{
		result[31 - list->len] = base[nbr % 16];
		nbr = nbr / 16;
		list->len++;
	}
	if (list->hash)
		*result = *(x_hash(base, result, &list));
	if (list->precision > list->len)
		return (x_prec(result, list));
	else if (list->minus == 1 && list->width > list->len)
		return (x_minus(result, list));
	else if (list->width > list->len)
		return (x_width(result, list));
	write(1, result + 32 - list->len, list->len);
	return (list->len);
}
