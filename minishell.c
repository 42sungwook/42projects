/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:58:44 by daijeong          #+#    #+#             */
/*   Updated: 2023/04/28 19:40:40 by daijeong         ###   ########.fr       */
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
		{
			end_of_word(cmds, token, str[i]);
		}
		else if (str[i] == '\"')
			parse_double_quote(token);
		else if (str[i] == '\'')
			parse_single_quote(token);
		// else if (str[i] == '<' || str[i] == '>')
		// 	parse_redirection(cmds, token);
		// else if (str[i] == '|')
		// 	parse_pipe(cmds, token);
		else if (str[i] == '$')
			parse_dollar(token);
		else if (token->dollar == 1)
			token->dollar_word = make_word_c(token->dollar_word, str[i]);
		else
			token->word = make_word_c(token->word, str[i]);
		// if (token->heredoc == 1)
		// 	read_heredoc(cmds);
	}
	end_of_word(cmds, token, str[i]);
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	int			temp_fd;
	t_commands	*cmds;
	t_commands 	*temp;
	t_token		*token;
	int			i;

	str = 0;
	cmds = init_cmds();
	temp = cmds;
	token = init_token(envp);
	while (1)
	{
		str = readline("minishell> : ");
		parse_line(str, temp, token); // 한 캐릭터씩 읽으면서 구조체에 실행시킬 명령어 저장
		// execute_cmds(cmds); // 명령어 실행
		add_history(str); // line 저장
		// free_line(str, cmds, token); // 사용이 끝난 line, 커맨드, 토큰 구조체 free
		// if (!str)
		// 	exit_shell();
		print_cmds(temp->cmd);
		temp->next = init_cmds();
		temp = temp->next;
	}
}

//exit long long 범위까지 256으로 나눠서 exit값 반환