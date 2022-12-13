/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:49:06 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/13 14:34:13 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	int				fd;
	char			*temp;
	struct s_list	*next;
}					t_list;

size_t		gnl_find(char *buff);
size_t		gnl_strlen(const char *s);
char		*gnl_strjoin(char *s1, char *s2);
t_list		*gnl_free(t_list *head, t_list *list);
t_list		*gnl_lstnew(int fd);
char		*get_next_line(int fd);

#endif