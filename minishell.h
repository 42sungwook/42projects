/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:58:34 by daijeong          #+#    #+#             */
/*   Updated: 2023/04/28 22:02:13 by daijeong         ###   ########.fr       */
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

typedef struct s_fds
{
	int		infile;
	int		outfile;
	char	*infile_name;
	char	*outfile_name;
	int		pipe1[2];
	int		pipe2[2];
}	t_fds;

typedef struct s_commands
{
	char				*infile;
	char				*outfile;
	int					infile_fd;
	int					outfile_fd;
	char				**cmd;
	int					exit_code;
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
	int		pipe;
	int		command;
	int		heredoc;
	int		left_redirection;
	int		right_redirection;
	char	*word;
	char	*dollar_word;
	char	prev_char;
}	t_token;

//init
t_token		*init_token(char **envp);
t_commands	*init_cmds(void);

//parsing
int			end_of_word(t_commands *cmds, t_token *token, char c);
char		*make_word_str(char *curr_word, char *c);
char		*make_word_c(char *curr_word, char c);
void		make_command(t_commands *cmds, char *word);
char		**add_cmd(char **cmd, char *word);

void		find_dollar_word_in_envp(t_token *token);
int			parse_dollar(t_token *token);
int			parse_single_quote(t_token *token);
int			parse_double_quote(t_token *token);

//print_cmds
int			print_cmds(char **str);

//pipex
int			execute_cmds(t_commands *cmds, char **envp);
int			check_access_and_save(t_commands *cmds, char **path, int i);
char		*join_path(char *str1, char *str2);
void		free_arr(char **arr);


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
