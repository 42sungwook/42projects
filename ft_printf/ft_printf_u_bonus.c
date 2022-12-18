/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:32 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/14 15:27:07 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static size_t	u_prec(char *result, t_list *list)
{
	while (list->blank < list->precision - list->len)
	{
		write(1, "0", 1);
		list->blank++;
	}
	write(1, result + 32 - list->len, list->len);
	return (list->len + list->blank);
}

static size_t	u_minus(char *result, t_list *list)
{
	write(1, result + 32 - list->len, list->len);
	while (list->blank < list->width - list->len)
	{
		write(1, " ", 1);
		list->blank++;
	}
	return (list->len + list->blank);
}

static size_t	u_width(char *result, t_list *list)
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

size_t	printf_u(unsigned int nbr, t_list *list)
{
	char		result[32];

	if (nbr == 0)
	{
		result[31] = '0';
		list->len++;
	}
	while (nbr > 0)
	{
		result[31 - list->len] = nbr % 10 + '0';
		nbr = nbr / 10;
		list->len++;
	}
	if (list->precision > list->len)
		return (u_prec(result, list));
	else if (list->minus == 1 && list->width > list->len)
		return (u_minus(result, list));
	else if (list->width > list->len)
		return (u_width(result, list));
	write(1, result + 32 - list->len, list->len);
	return (list->len);
}
