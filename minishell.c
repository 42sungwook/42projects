/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:58:44 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/20 21:32:17 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_character(t_commands *cmds, t_token *token, char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (end_of_word(cmds, token, c));
	else if (c == '\"')
		return (parse_double_quote(cmds, token));
	else if (c == '\'')
		return (parse_single_quote(cmds, token));
	else if (c == '<' || c == '>')
		return (parse_redirection(cmds, token, c));
	else if (c == '$')
		return (parse_dollar(token));
	else if (c == '?')
		return (parse_question(token));
	return (1);
}

int	parse_syntax_error(t_commands *cmds, t_token *token, int flag)
{
	if ((((token->pipe >= 1 && !cmds->cmd) || (token->left_redirection || \
		token->right_redirection)) && (!token->word && !token->dollar_word)) || \
		token->quote || flag == 1)
	{
		write(2, "minishell: syntax error\n", 24);
		g_exit_status = SYNTAX_ERROR;
		return (1);
	}
	return (0);
}

int	parse_line(char *str, t_commands *cmds, t_token *token)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (str[++i] && flag == 0)
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
			str[i] == '\"' || str[i] == '<' || str[i] == '>' || \
			str[i] == '\'' || str[i] == '$' || str[i] == '?')
			flag = parse_character(cmds, token, str[i]);
		else if (str[i] == '|' && !token->quote)
			flag = parse_pipe(&cmds, token);
		else if (token->dollar == 1)
			token->dollar_word = make_word_c(token->dollar_word, str[i]);
		else
			token->word = make_word_c(token->word, str[i]);
	}
	if (parse_syntax_error(cmds, token, flag))
		return (1);
	end_of_word(cmds, token, str[i]);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_commands	*cmds;
	t_token		*token;

	str = 0;
	g_exit_status = 0;
	cmds = init_cmds();
	token = init_token(envp, argc, argv);
	while (1)
	{	
		init_signal();
		str = readline("minishell> : ");
		if (!str)
		{
			write(2, "exit\n", 5);
			exit(g_exit_status);
		}
		del_signal();
		if (!parse_line(str, cmds, token))
			execute_cmds(cmds, token);
		add_history(str);
		free_everything(cmds, token, str);
		cmds = init_cmds();
	}
}
