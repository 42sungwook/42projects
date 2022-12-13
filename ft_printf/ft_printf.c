/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:18:06 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/13 21:45:36 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_inspect(char c)
{
	if (!c)
		return (0);
	else if (c == 'd' || c == 'c' || c == 's' || c == 'p' || \
			c == 'u' || c == 'i' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

static int	print_something(va_list *ap, char c)
{
	int	count;

	count = 0;
	if (c == 'd' || c == 'i')
		count += printf_di(va_arg(*ap, int));
	else if (c == 's')
		count += printf_s(va_arg(*ap, char *));
	else if (c == 'p')
		count += printf_p(va_arg(*ap, long long));
	else if (c == 'u')
		count += printf_u(va_arg(*ap, unsigned int));
	else if (c == 'c')
		count += printf_c(va_arg(*ap, int));
	else if (c == 'x')
		count += printf_x(va_arg(*ap, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		count += printf_x(va_arg(*ap, unsigned int), "0123456789ABCDEF");
	else if (c == '%')
		count += printf_c('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	int			i;
	int			count;

	i = 0;
	count = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (ft_inspect(str[i + 1]) == 0)
				return (-1);
			count += print_something(&ap, str[i + 1]);
			i++;
		}
		else
			count += printf_c(str[i]);
		i++;
	}
	va_end(ap);
	return (count);
}