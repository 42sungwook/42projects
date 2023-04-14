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
	char			**cmd;
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

//utils
char		*join_path(char *str1, char *str2);
t_arguments	*init_args(int argc, char **argv, char **envp);
void		make_cmdlist(t_arguments *args, char **cmds);
t_list		*cmd_addlist(char **cmds);
size_t		ft_strlen(const char *s);
void		free_arr(char **arr);
void		nth_child_process2(t_arguments *args, t_list *temp, int sign);


//ft_split
char		**ft_split(char const *s, char c);

//pipex
void		pipex(t_arguments *args);

#endif
