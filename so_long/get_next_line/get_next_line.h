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