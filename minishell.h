/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:58:34 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/01 21:17:18 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <string.h>

# define READ_END 0
# define WRITE_END 1
# define NULL_ENVP "0"
# define INFILE_END 0
# define HEREDOC_END 1

typedef struct s_line
{
	char			*line;
	int				flag;
	struct s_line	*next;
}	t_line;

typedef struct s_pipe
{
	int		pipe1[2];
	int		pipe2[2];
}	t_pipe;

typedef struct s_fds
{
	int		infile;
	int		outfile;
}	t_fds;

typedef struct s_commands
{
	t_line				*infile; //list로 바꿔야함
	t_line				*infile_end;
	t_line				*outfile; //list로 바꿔야함
	t_line				*outfile_end;
	char				**cmd;
	t_line				*heredoc; //list로 바꿔서 limiter 받아줘야함
	t_line				*heredoc_end;
	int					read_heredoc;
	t_fds				*fds;
	struct s_commands	*next;
}	t_commands;

typedef struct s_envp
{
	char			*str;
	struct s_envp	*next;
}	t_envp;

typedef struct s_token
{
	t_envp	*envp;
	char	quote;
	int		dollar;
	char	*dollar_word;
	int		pipe;
	int		command;
	int		left_redirection;
	int		right_redirection;
	char	*word;
	char	prev_char;
	int		exit_status;
}	t_token;

//init
t_token		*init_token(char **envp);
t_commands	*init_cmds(void);
t_line		*init_line(void);


//parsing
int			end_of_word(t_commands *cmds, t_token *token, char c);
char		*make_word_str(char *curr_word, char *c);
char		*make_word_c(char *curr_word, char c);
void		make_command(t_commands *cmds, t_token *token);
char		**add_cmd(char **cmd, char *word);

void		find_dollar_word_in_envp(t_token *token);
int			parse_dollar(t_token *token);
int			parse_single_quote(t_token *token);
int			parse_double_quote(t_token *token);
int			parse_redirection(t_commands *cmds, t_token *token, char c);


//print_cmds
int			print_cmds(char **str);

//pipex
void		save_cmds(t_commands *cmds, char **envp);
int			execute_cmds(t_commands *cmds, t_token *token);
pid_t		last_child_process1(t_commands *cmds, char **envp, t_pipe *pipe_fd);
pid_t		last_child_process2(t_commands *cmds, char **envp, t_pipe *pipe_fd);
int			nth_child_process(t_commands *cmds, pid_t pid, char **envp, t_pipe *pipe_fd);
void		first_child_process(t_commands *cmds, pid_t pid, char **envp, t_pipe *pipe_fd);
void		save_fds_in_cmds(t_commands *cmds);
void		init_cmds_fds(t_commands *cmds);
void		pipex(t_commands *cmds, char **envp, t_pipe *pipe_fd);
void		open_infile_list(t_commands *cmds);
void		open_outfile_list(t_commands *cmds);

//main
void		free_arr(char **arr);

//free
void		free_everything(t_commands **cmds, t_token *token, char *str);


// void		pipex(t_arguments *args);
// //heredoc
// char		*ft_strjoin(char const *s1, char const *s2);
// void		open_files_heredoc(t_arguments *args);
// int			pipex_strcmp(char *str1, char *str2);
// void		heredoc_pipex(t_arguments *args);

// //utils
// t_arguments	*init_args(int argc, char **argv, char **envp);
// void		make_cmdlist(t_arguments *args, char **cmds);
// t_list		*cmd_addlist(char **cmds);
// void		save_no_path(t_arguments *args, int i);
// int			nth_child_process_even(pid_t pid, t_arguments *args, t_list *temp);
// int			nth_child_process_odd(pid_t pid, t_arguments *args, t_list *temp);
#endif
