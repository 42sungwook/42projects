/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:17 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/25 19:12:25 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_dollar(t_token *token)
{
	if (token->dollar == 1)
	{
		if (token->prev_char == '$')
		{
			if (token->word)
				token->word = make_word_str(token->word, "$$");
			else
				token->word = ft_strdup("$$");
			token->dollar = 0;
		}
		else
		{
			find_dollar_word_in_envp(token);
			token->dollar = 1;
		}
	}
	else if (token->quote == 0 || token->quote == '\"')
		token->dollar = 1;
	else if (token->dollar == 0 && token->quote == '\'')
		token->word = make_word_c(token->word, '$');
	else
		token->dollar = 1;
	token->prev_char = '$';
	return (0);
}
