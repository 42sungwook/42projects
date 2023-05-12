/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:58:44 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/12 16:27:13 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_line(char *str, t_commands *cmds, t_token *token)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') //white space 추가
			end_of_word(cmds, token, str[i]);
		else if (str[i] == '\"')
			parse_double_quote(cmds, token);
		else if (str[i] == '\'')
			parse_single_quote(cmds, token);
		else if (str[i] == '<' || str[i] == '>')
			parse_redirection(cmds, token, str[i]);
		else if (str[i] == '|')
			cmds = parse_pipe(cmds, token);
		else if (str[i] == '$')
			parse_dollar(token);
		else if (str[i] == '?')
			parse_question(token);
		else if (token->dollar == 1)
			token->dollar_word = make_word_c(token->dollar_word, str[i]);
		else
			token->word = make_word_c(token->word, str[i]);
	}
	end_of_word(cmds, token, str[i]);
}

// void	check_leak(void)
// {
// 	system("leaks minishell");
// }

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_commands	*cmds;
	t_token		*token;

	str = 0;
	g_exit_status = 0;
	(void)argc;
	(void)argv;
	// atexit(check_leak);
	cmds = init_cmds();
	token = init_token(envp);
	while (1)
	{	
		init_signal();
		str = readline("minishell> : ");
		if (!str)
		{
			write(2, "exit\n", 5);
			exit(0);
		}
		parse_line(str, cmds, token);
		del_signal();
		execute_cmds(cmds, token);
		add_history(str);
		free_everything(cmds, token, str);
		cmds = init_cmds();
	}
}

//exit long long 범위까지 256으로 나눠서 exit값 반

// exit status 만들어야함
// ctrl D 눌렀을 때
// exit command 입력했을 때
// $? 처리 -> exit status로 치환

//heredoc EOF일때 unlink 처리

