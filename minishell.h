/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:58:34 by daijeong          #+#    #+#             */
/*   Updated: 2023/04/27 15:58:35 by daijeong         ###   ########.fr       */
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


# define NULL_ENVP "0"

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

typedef struct s_token
{
	char	**envp;
	char	quote;
	int		double_quote; //필요 여부 고려
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
int		end_of_word(t_commands *cmds, t_token *token, char c);
char	*make_word_str(char *curr_word, char *c);
char	*make_word_c(char *curr_word, char c);
void	make_command(t_commands *cmds, char *word);
char	**add_cmd(char **cmd, char *word);


#endif
