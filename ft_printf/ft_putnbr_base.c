/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:36:32 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/01 19:10:53 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(int nbr, char *base)
{
	int				len;
	char			result[32];
	unsigned int	digit;

	digit = 16;
	len = 0;
	if (nbr < 0)
		nbr *= -1;
	if (nbr == 0)
	{
		write(1, &base[0], 1);
		return (1);
	}
	while (nbr != 0)
	{
		result[31 - len] = base[nbr % digit];
		nbr = nbr / digit;
		len++;
	}
	write(1, result + 31 - len, len);
	return (len);
}
