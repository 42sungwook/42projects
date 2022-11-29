/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:18:06 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/29 20:56:04 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_inspect(char c)
{
	if (c == 'd' || c == 'c' || c == 's' || c == 'p' || \
			c == 'u' || c == 'i' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

void	print_something(va_list *ap, char c)
{
	if (c == 'd')
		ft_putstr_fd(ft_itoa(va_arg(*ap, int)), 1);
	else if (c == 'i')
		ft_putstr_fd(ft_itoa(va_arg(*ap, int)), 1);
	else if (c == 's')
		ft_putstr_fd(va_arg(*ap, char *), 1);
	else if (c == 'p')
		ft_putnbr_base(va_arg(*ap, long long), "0123456789abcdef");
	else if (c == 'u')
		ft_putnbr_fd(va_arg(*ap, unsigned int), 1);
	else if (c == 'c')
		ft_putchar_fd(va_arg(*ap, int), 1);
	else if (c == 'x')
		ft_putnbr_base((long long)va_arg \
			(*ap, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		ft_putnbr_base((long long)va_arg \
			(*ap, unsigned int), "0123456789ABCDEF");
	else if (c == '%')
		write(1, "%", 1);
}

int	ft_printf(char *str, ...)
{
	va_list		ap;
	size_t		i;

	i = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (ft_inspect(str[i + 1]))
				print_something(&ap, str[i + 1]);
			else
				return (-1);
			i += 2;
		}
		else
			write(1, &str[i], 1);
		i++;
	}
	va_end(ap);
	return (0);
}

int	main(void)
{
	int	a = 621251351;
	int	b = 2;
	char	str[5] = "abc";

	int		*ptr = &b;
	char	d = 'd';
	ft_printf("%p\n", ptr);
	printf("%p\n", ptr);
	return (0);
}
