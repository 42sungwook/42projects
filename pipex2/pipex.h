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

typedef struct s_list
{
	char			**cmds;
	struct s_list	*next;
}	t_list;

typedef struct s_fds
{
	int		infile;
	int		outfile;
	char	*infile_name;
	char	*outfile_name;
	int		pipe1[2];
	int		pipe2[2];
}	t_fds;

typedef struct s_arguments
{
	int		argc;
	char	**argv;
	char	**envp;
	int		cmd_count;
	t_list	*cmds;
	t_fds	*fds;
}	t_arguments;

//ft_split
char	**ft_split(char const *s, char c);

#endif
