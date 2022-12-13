/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:18:06 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/13 21:56:14 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_inspect(char c)
{
	if (!c)
		return (0);
	else if (c == 'd' || c == 'i')
		return (1);
	else if (c == 'c')
		return (2);
	else if (c == 's')
		return (3);
	else if (c == 'p')
		return (4);
	else if (c == 'u')
		return (5);
	else if (c == 'x' || c == 'X')
		return (6);
	else if (c == '%')
		return (7);
	return (0);
}

static size_t	print_something(va_list *ap, t_list *list)
{
	size_t	count;

	count = 0;
	if (list->conversion == 'd' || list->conversion == 'i')
		count += printf_di(va_arg(*ap, int));
	else if (list->conversion == 's')
		count += printf_s(va_arg(*ap, char *), list);
	else if (list->conversion == 'p')
		count += printf_p(va_arg(*ap, long long), list);
	else if (list->conversion == 'u')
		count += printf_u(va_arg(*ap, unsigned int), list);
	else if (list->conversion == 'c')
		count += printf_c(va_arg(*ap, int), list);
	else if (list->conversion == 'x')
		count += printf_x(va_arg(*ap, unsigned int), "0123456789abcdef", list);
	else if (list->conversion == 'X')
		count += printf_x(va_arg(*ap, unsigned int), "0123456789ABCDEF", list);
	else if (list->conversion == '%')
		count += printf_c('%', list);
	return (count);
}

static t_list	*ft_check_error(char *str, t_list *list)
{
	size_t	i;
	int		conversion;

	i = 0;
	while (str[i])
	{
		conversion = ft_inspect(str[i]);
		if (conversion != 0)
			break ;
		i++;
	}
	if (str[i] == 0)
		return (0);
	list = printf_lstadd(str[i], i);
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
			list = ft_check_error(&str[i + 1], list);
			if (!list)
				return (-1);
			count += print_something(&ap, list);
			i++;
		}
		else
			count += printf_c(str[i]);
		i++;
	}
	va_end(ap);
	return (count);
}
