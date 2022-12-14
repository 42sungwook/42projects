/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:18:06 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/14 16:38:06 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	printf_inspect(char c)
{
	if (c == 'd' || c == 'i')
		return (1);
	else if (c == 's')
		return (2);
	else if (c == 'p')
		return (3);
	else if (c == 'u')
		return (4);
	else if (c == 'c')
		return (5);
	else if (c == 'x')
		return (6);
	else if (c == 'X')
		return (7);
	else if (c == '%')
		return (8);
	return (0);
}

static size_t	print_something(va_list *ap, t_list *list)
{
	size_t	count;

	count = 0;
	if (list->conversion == 1)
		count += printf_di(va_arg(*ap, int), list);
	else if (list->conversion == 2)
		count += printf_s(va_arg(*ap, char *), list);
	else if (list->conversion == 3)
		count += printf_p(va_arg(*ap, long long), list);
	else if (list->conversion == 4)
		count += printf_u(va_arg(*ap, unsigned int), list);
	else if (list->conversion == 5)
		count += printf_c(va_arg(*ap, int), list);
	else if (list->conversion == 6)
		count += printf_x(va_arg(*ap, unsigned int), "0123456789abcdef", list);
	else if (list->conversion == 7)
		count += printf_x(va_arg(*ap, unsigned int), "0123456789ABCDEF", list);
	else if (list->conversion == 8)
		count += printf_c('%', list);
	return (count);
}

static t_list	*ft_check_error(const char *str, size_t i)
{
	t_list	*list;
	size_t	j;

	j = 0;
	list = malloc(sizeof(t_list));
	list = printf_init_list(list);
	while (str[i + j])
	{
		list->conversion = printf_inspect(str[i + j]);
		if (list->conversion != 0)
			break ;
		j++;
	}
	if (str[i + j] == 0)
		return (0);
	list = printf_makelst(str, i, j, list);
	list->str_len = j;
	return (list);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	size_t		i;
	size_t		count;
	t_list		*list;

	i = 0;
	count = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			list = ft_check_error(str, i + 1);
			if (!list)
				return (-1);
			count += print_something(&ap, list);
			i += list->str_len + 1;
			free(list);
		}
		else
			count += printf_putchar(str[i]);
		i++;
	}
	va_end(ap);
	return (count);
}
