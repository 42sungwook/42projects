/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:02:02 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/14 14:51:49 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h> 

size_t	printf_c(char s);
size_t	printf_s(char *s);
size_t	printf_p(unsigned long long arr);
size_t	printf_u(unsigned int nbr);
size_t	printf_x(unsigned int nbr, char *base);
size_t	printf_di(int nbr);
int		ft_printf(const char *str, ...);

#endif