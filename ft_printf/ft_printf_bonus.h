/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:02:02 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/14 16:20:30 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h> 
# include <stdlib.h>

typedef struct s_list
{
	int	space;
	int	plus;
	int	minus;
	int	zero;
	int	hash;
	int	precision;
	int	width;
	int	conversion;
	int	len;
	int	str_len;
	int	sign;
	int	blank;
}					t_list;

int		printf_inspect(char c);
size_t	printf_di(int nbr, t_list *list);
size_t	printf_p(unsigned long long arr, t_list *list);
size_t	printf_s(char *str, t_list *list);
size_t	printf_c(char c, t_list *list);
size_t	printf_u(unsigned int nbr, t_list *list);
size_t	printf_x(unsigned int nbr, char *base, t_list *list);
size_t	printf_putchar(char c);
t_list	*printf_init_list(t_list *list);
size_t	printf_width(const char *str, size_t idx, t_list **list);
size_t	printf_precision(const char *str, size_t idx, t_list **list);
t_list	*printf_makelst(const char *str, size_t idx, size_t len, t_list *list);
int		ft_printf(const char *str, ...);

#endif