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

typedef struct s_arguments
{
    int     argc;
    char    **argv;
    char    **envp;
}   t_arguments;

typedef struct s_flist
{
    int             pipe[2];
    struct s_flist  *next;
}   t_flist;

typedef struct s_plist
{
    pid_t           pid;
    struct s_plist   *next;
}   t_plist;

typedef struct s_fds
{
    int     infile;
    int     outfile;
    char    *infile_name;
    char    *outfile_name;
    t_flist *pipe_fd;
}   t_fds;

//open file
t_fds   open_files(char **argv);

//save path
char    **save_paths(char **envp);

//child process
char *join_path(char *path, char *cmd);
// int child_process(t_fds fds, char **argv, char **paths, t_list **pids, char **envp);

//parent process
// int parent_process(t_fds fds,t_list *pids);

//ft_split
char	**ft_split(char const *s, char c);

#endif
