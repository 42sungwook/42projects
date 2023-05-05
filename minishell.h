/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:58:34 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/05 17:46:10 by sungwook         ###   ########.fr       */
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
# define CLOSE_PIPE1 1
# define CLOSE_PIPE2 2
# define CLOSE_BOTH 3

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
	t_line				*infile;
	t_line				*infile_end;
	t_line				*outfile;
	t_line				*outfile_end;
	char				**cmd;
	t_line				*heredoc;
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
t_envp		*init_envp(char **envp);

//parsing
void		end_of_word(t_commands *cmds, t_token *token, char c);
char		*make_word_str(char *curr_word, char *c);
char		*make_word_c(char *curr_word, char c);
void		make_command(t_commands *cmds, t_token *token);
char		**add_cmd(char **cmd, char *word);

void		find_dollar_word_in_envp(t_token *token);
int			parse_dollar(t_token *token);
int			parse_single_quote(t_commands *cmds, t_token *token);
int			parse_double_quote(t_commands *cmds, t_token *token);
int			parse_redirection(t_commands *cmds, t_token *token, char c);
t_commands	*parse_pipe(t_commands *cmds, t_token *token);

//print_cmds
int			print_cmds(char **str);

//execute_cmds
void		save_cmds(t_commands *cmds, char **envp);
int			execute_cmds(t_commands *cmds, t_token *token);
pid_t		last_child_process1(t_commands *cmds, t_token *token, \
			t_pipe *pipe_fd);
pid_t		last_child_process2(t_commands *cmds, t_token *token, \
			t_pipe *pipe_fd);
int			nth_child_process(t_commands *cmds, pid_t pid, \
			t_token *token, t_pipe *pipe_fd);
void		first_child_process(t_commands *cmds, pid_t pid, \
			t_token *token, t_pipe *pipe_fd);
void		save_fds_in_cmds(t_commands *cmds);
void		init_cmds_fds(t_commands *cmds);
void		pipex(t_commands *cmds, t_token *token, t_pipe *pipe_fd);
void		open_infile_list(t_commands *cmds);
void		open_outfile_list(t_commands *cmds);
void		child_process_check_fd(t_commands *cmds);
void		close_pipe(t_pipe *pipe_fd, int flag);
void		close_all_fds(t_commands *cmds);
char		**make_two_pointer_envp(t_token *token);

//main
void		free_arr(char **arr);

//free
void		free_everything(t_commands *cmds, t_token *token, char *str);

//heredoc
void		open_heredoc(t_commands *cmds);

//builtins
int			check_builtins(t_commands	*cmds);
int			execute_builtins(t_commands *cmds, t_token *token);
int			builtin_cd(t_commands *cmds, t_token *token);
int			builtin_echo(t_commands *cmds);
int			builtin_env(t_token *token);
int			builtin_pwd(void);
int			builtin_unset(t_token *token, char **cmd);


#endif
