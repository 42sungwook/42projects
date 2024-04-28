/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:09:24 by sungwook          #+#    #+#             */
/*   Updated: 2023/04/15 17:33:23 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define READ_END 0
# define WRITE_END 1
# define BUFFER_SIZE 42

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
	int		heredoc;
	pid_t	hd_pid;
}	t_arguments;

//pipex
void		pipex(t_arguments *args);

//ft_split
char		**ft_split(char const *s, char c);

//heredoc
char		*ft_strjoin(char const *s1, char const *s2);
void		open_files_heredoc(t_arguments *args);
int			pipex_strcmp(char *str1, char *str2);
void		heredoc_pipex(t_arguments *args);

//get_next_line
char		*get_next_line(int fd);
size_t		gnl_find(char *buff);
size_t		gnl_strlen(const char *s);
char		*gnl_strjoin(char *s1, char *s2, size_t i, size_t j);

//utils
char		*join_path(char *str1, char *str2);
t_arguments	*init_args(int argc, char **argv, char **envp);
void		make_cmdlist(t_arguments *args, char **cmds);
t_list		*cmd_addlist(char **cmds);
size_t		ft_strlen(const char *s);
void		free_arr(char **arr);
int			check_access_and_save(t_arguments *args, char **path, int i);
void		save_no_path(t_arguments *args, int i);
int			nth_child_process_even(pid_t pid, t_arguments *args, t_list *temp);
int			nth_child_process_odd(pid_t pid, t_arguments *args, t_list *temp);

#endif
