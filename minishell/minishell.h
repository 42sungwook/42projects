/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:58:34 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/18 17:15:33 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <string.h>
# include <sys/stat.h>

# define ASCII_ZERO 48
# define READ_END 0
# define WRITE_END 1
# define NULL_ENVP "0"
# define INFILE_END 0
# define HEREDOC_END 1
# define CLOSE_PIPE1 1
# define CLOSE_PIPE2 0
# define CLOSE_BOTH 3
# define SYNTAX_ERROR 258
# define CMD_NOT_FOUND 127
# define IS_DIR 126

int	g_exit_status;

typedef struct s_line
{
	char			*line;
	int				flag;
	struct s_line	*next;
}	t_line;

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
	int		pipe_fd[2];
	int		prev_fd;
	int		left_redirection;
	int		right_redirection;
	char	*word;
	char	prev_char;
	pid_t	pid;
}	t_token;

//init
t_token		*init_token(char **envp, int argc, char **argv);
t_commands	*init_cmds(void);
t_line		*init_line(void);
t_envp		*init_envp(char **envp);

//parsing
int			end_of_word(t_commands *cmds, t_token *token, char c);
char		*make_word_str(char *curr_word, char *c);
char		*make_word_c(char *curr_word, char c);
void		make_command(t_commands *cmds, t_token *token);
char		**add_cmd(char **cmd, char *word);

int			find_dollar_word_in_envp(t_token *token);
int			parse_dollar(t_token *token);
int			parse_single_quote(t_commands *cmds, t_token *token);
int			parse_double_quote(t_commands *cmds, t_token *token);
int			parse_redirection(t_commands *cmds, t_token *token, char c);
int			parse_pipe(t_commands **cmds, t_token *token);
int			parse_question(t_token *token);

//execute_cmds
int			save_cmds(t_commands *cmds, char **envp);
int			execute_cmds(t_commands *cmds, t_token *token);
int			save_fds_in_cmds(t_commands *cmds);
int			is_directory(const char *path);
void		init_cmds_fds(t_commands *cmds);
void		pipex(t_commands *cmds, t_token *token);
char		**make_two_pointer_envp(t_token *token);

//main
void		free_arr(char **arr);
int			cmpcmp(char *str, char c);

//merge
void		merge_sort(t_envp **list, size_t size);

//free
void		free_everything(t_commands *cmds, t_token *token, char *str);

//heredoc
int			open_heredoc(t_commands *cmds);

//signal
void		init_signal(void);
void		del_signal(void);
void		init_child_signal(void);
void		init_heredoc_signal(void);

//builtins
int			check_builtins(t_commands	*cmds);
int			execute_builtins(t_commands *cmds, t_token *token);
int			builtin_cd(t_commands *cmds, t_token *token);
int			builtin_echo(t_commands *cmds);
int			builtin_env(t_commands *cmds, t_token *token);
int			builtin_pwd(t_commands *cmds, t_token *token);
int			builtin_unset(t_token *token, char **cmd);
int			builtin_export(t_commands *cmds, t_token *token, char **cmd);
int			builtin_exit(t_commands *cmds);
t_envp		*delete_envp_list(t_envp *envp_list, t_envp *tmp_list);
int			envp_lstsize(t_envp *lst);
int			print_envp_list(t_commands *cmds, t_envp *envp);
void		print_export_message(t_commands *cmds, t_envp *free_tmp);
void		envp_lstadd_back(t_envp **lst, t_envp *new);
t_envp		*delete_envp_list(t_envp *envp_list, t_envp *tmp_list);
t_envp		*ft_listdup(t_envp *envp);
char		*find_current_dir(t_token *token);
int			check_valid_cmd(char *cmd, char *str, int len);

#endif
