/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:32 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/14 16:30:41 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

size_t	printf_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

t_list	*printf_init_list(t_list *list)
{
	list->space = 0;
	list->plus = 0;
	list->minus = 0;
	list->zero = 0;
	list->hash = 0;
	list->width = 0;
	list->precision = 0;
	list->conversion = 0;
	list->len = 0;
	list->sign = 0;
	list->blank = 0;
	list->str_len = 0;
	return (list);
}

size_t	printf_width(const char *str, size_t idx, t_list **list)
{
	size_t	i;
	int		num;

	i = 0;
	num = 0;
	while (printf_inspect(str[idx + i]) != 0)
	{
		if (str[idx + i] >= '0' && str[idx + i] <= '9')
			num = num * 10 + str[i] - '0';
		else if (str[idx + i] == ' ' || str[idx + i] == '+' || \
			str[idx + i] == '0' || str[idx + i] == '#' || \
			str[idx + i] == '-' || str[idx + i] == '.')
			break ;
		i++;
	}
	(*list)->width = num;
	return (i);
}

size_t	printf_precision(const char *str, size_t idx, t_list **list)
{
	size_t	i;
	int		num;

	i = 0;
	num = 0;
	while (printf_inspect(str[idx + i]) != 0)
	{
		if (str[idx + i] >= '0' && str[idx + i] <= '9')
			num = num * 10 + str[i] - '0';
		else if (str[idx + i] == ' ' || str[idx + i] == '+' || \
			str[idx + i] == '0' || str[idx + i] == '#' || \
			str[idx + i] == '-' || str[idx + i] == '.')
			break ;
		i++;
	}
	(*list)->precision = num;
	return (i + 1);
}

t_list	*printf_makelst(const char *str, size_t idx, size_t len, t_list *list)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (str[idx + i] == ' ')
			list->space = 1;
		else if (str[idx + i] == '+')
			list->plus = 1;
		else if (str[idx + i] == '-')
			list->minus = 1;
		else if (str[idx + i] == '0')
			list->zero = 1;
		else if (str[idx + i] == '#')
			list->hash = 1;
		else if (str[idx + i] >= '1' && str[i] <= '9' && list->width == 0)
			i += printf_width(str, idx + i, &list);
		else if (str[idx + i] == '.' && list->precision == 0)
			i += printf_precision(str, idx + i + 1, &list);
		i++;
	}
	return (list);
}
