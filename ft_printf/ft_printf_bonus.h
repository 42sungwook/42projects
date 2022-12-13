/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:02:02 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/13 21:47:04 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h> 
# include <stdlib.h>

typedef struct s_list
{
	char			flag;
	int				width;
	int				precision;
	char			conversion;
	struct s_list	*next;
}					t_list;

size_t	printf_c(char s, t_list *list);
size_t	printf_s(char *s, t_list *list);
size_t	printf_p(unsigned long long arr, t_list *list);
size_t	printf_u(unsigned int nbr, t_list *list);
size_t	printf_x(unsigned int nbr, char *base, t_list *list);
size_t	printf_di(int nbr, t_list *list);
int		ft_printf(const char *str, ...);

#endif