/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:44:08 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/27 21:22:50 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*temp;
	struct s_list	*next;
	int				fd;
}					t_list;

size_t		find_nl(char *buff);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_make_remain(char *temp);
char		*ft_make_line(char *temp);
char		*ft_get_line(int fd, char *temp);
char		*get_next_line(int fd);
char		*get_next_line2(t_list *list);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
#endif