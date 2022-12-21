/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:49:06 by sungwook          #+#    #+#             */
/*   Updated: 2022/12/21 12:31:35 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t		gnl_find(char *buff);
size_t		gnl_strlen(const char *s);
char		*gnl_strjoin(char *s1, char *s2, size_t i, size_t j);
char		*get_next_line(int fd);

#endif