/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:11 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/25 17:14:00 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_double_quote_find_envp(t_token *token)
{
	if (token->dollar_word)
		find_dollar_word_in_envp(token);
	if (token->quote)
		token->quote = 0;
	else
		token->quote = '\"';
	token->dollar = 0;
}

int	parse_double_quote(t_commands *cmds, t_token *token)
{
	if (token->quote == '\"' && token->prev_char == '\"' && token->word == 0)
	{
		token->quote = 0;
		cmds->cmd = add_cmd(cmds->cmd, token->word);
		return (0);
	}
	if (token->quote == 0 && token->dollar == 0)
		token->quote = '\"';
	else if (token->quote == '\"' && token->dollar == 0)
		token->quote = 0;
	else if ((token->quote == '\"' && token->dollar == 1) || \
			(token->quote == 0 && token->dollar == 1))
		parse_double_quote_find_envp(token);
	if (token->quote == '\'')
		token->word = make_word_c(token->word, '\"');
	token->prev_char = '\"';
	return (0);
}
