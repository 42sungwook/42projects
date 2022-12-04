/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:18:06 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/04 11:18:14 by sungwook         ###   ########.fr       */
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
		count += ft_free_putstr(ft_itoa(va_arg(*ap, int)));
	else if (c == 's')
		count += ft_putstr(va_arg(*ap, char *));
	else if (c == 'p')
		count += ft_address(va_arg(*ap, long long));
	else if (c == 'u')
		count += ft_putnbr(va_arg(*ap, unsigned int));
	else if (c == 'c')
		count += ft_putchar(va_arg(*ap, int));
	else if (c == 'x')
		count += ft_putnbr_base(va_arg(*ap, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		count += ft_putnbr_base(va_arg(*ap, unsigned int), "0123456789ABCDEF");
	else if (c == '%')
		count += ft_putchar('%');
	return (count);
}

static int	ft_check_error(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (ft_inspect(str[i + 1]) == 0)
				return (-1);
			i++;
		}
		i++;
	}
	return (1);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	int			i;
	int			count;

	i = 0;
	count = 0;
	if (ft_check_error(str) == -1)
		return (-1);
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += print_something(&ap, str[i + 1]);
			i++;
		}
		else
			count += write(1, &str[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}
