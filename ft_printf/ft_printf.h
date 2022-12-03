/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:02:02 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/01 19:42:45 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h> 
# include <stdlib.h>

int		ft_address(unsigned long long arr);
int		ft_ul_len_n(unsigned long long n);
int		ft_len_n(int n);
char	*ft_itoa(int n);
int		ft_printf(const char *str, ...);
int		ft_putchar(char c);
int		ft_putnbr_base(unsigned int nbr, char *base);
int		ft_putnbr(unsigned int n);
int		ft_putstr(char *s);
int		ft_free_putstr(char *s);

#endif