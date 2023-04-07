#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>

# define READ_END 0
# define WRITE_END 1

typedef struct s_fds
{
    int     fd3;
    int     fd4;
    int     pipe_fd[2];
    char    *infile;
    char    *outfile;
}   t_fds;

typedef struct s_list
{
    pid_t           pid;
    struct s_list   *next;
}   t_list;

char	**ft_split(char const *s, char c);


#endif
