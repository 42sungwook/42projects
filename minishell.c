/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:58:44 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/01 21:21:44 by sungwook         ###   ########.fr       */
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
			parse_double_quote(token);
		else if (str[i] == '\'')
			parse_single_quote(token);
		else if (str[i] == '<' || str[i] == '>')
			parse_redirection(cmds, token, str[i]);
		// else if (str[i] == '|')
		// 	parse_pipe(cmds, token);
		else if (str[i] == '$')
			parse_dollar(token);
		else if (token->dollar == 1)
			token->dollar_word = make_word_c(token->dollar_word, str[i]);
		else
			token->word = make_word_c(token->word, str[i]);
	}
	end_of_word(cmds, token, str[i]);
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_commands	*cmds;
	t_commands	*temp;
	t_token		*token;

	str = 0;
	(void)argc;
	(void)argv;
	cmds = init_cmds();
	temp = cmds;
	token = init_token(envp);
	while (1)
	{
		str = readline("minishell> : ");
		if (!str || ft_strcmp(str, "exit") == 0)
			exit(0);
		parse_line(str, temp, token); // 한 캐릭터씩 읽으면서 구조체에 실행시킬 명령어 저장
		execute_cmds(temp, token); // 명령어 실행
		add_history(str); // line 저장
		// free_everything(&cmds, token, str); // 사용이 끝난 line, 커맨드, 토큰 구조체 free
		// print_cmds(temp->cmd);
		temp->next = init_cmds();
		temp = temp->next;
	}
}

//exit long long 범위까지 256으로 나눠서 exit값 반환