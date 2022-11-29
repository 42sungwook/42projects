/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:02:02 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/29 20:56:19 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h> 
# include <stdlib.h>
# include <stdio.h>

int		ft_len_n(int n);
char	*ft_negative_itoa(int n);
char	*ft_itoa(int n);
void	ft_print_result(char *base, long long nbr, int digit);
void	ft_putnbr_base(int nbr, char *base);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *s);
void	ft_putnbr_fd(int n, int fd);
void	ft_recursive(int n, int fd);
int		ft_printf(char *str, ...);
void	print_something(va_list *ap, char c);
int		ft_inspect(char c);

#endif