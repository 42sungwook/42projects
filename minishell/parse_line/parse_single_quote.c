/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_single_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:00 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/25 16:40:21 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_single_quote(t_commands *cmds, t_token *token)
{
	if (token->quote == '\'' && token->prev_char == '\'' && token->word == 0)
	{
		token->quote = 0;
		cmds->cmd = add_cmd(cmds->cmd, token->word);
		return (0);
	}
	if (token->quote != '\'')
	{
		if (token->dollar)
		{
			if (token->dollar_word)
				find_dollar_word_in_envp(token);
			else if (token->quote == '\"')
				token->word = make_word_c(token->word, '$');
			token->dollar = 0;
		}
		if (token->quote == '\"')
			token->word = make_word_c(token->word, '\'');
		else
			token->quote = '\'';
	}
	else if (token->quote == '\'')
		token->quote = 0;
	token->prev_char = '\'';
	return (0);
}