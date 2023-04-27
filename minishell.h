#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>


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

#endif
