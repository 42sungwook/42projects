/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:56:02 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/01 13:49:09 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	len;

	len = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[len] != 0)
	{
		ft_putchar(s[len]);
		len++;
	}
	return (len);
}

int	ft_free_putstr(char *s)
{
	int	len;

	len = 0;
	while (s[len] != 0)
	{
		ft_putchar(s[len]);
		len++;
	}
	free (s);
	return (len);
}
