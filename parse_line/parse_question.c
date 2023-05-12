/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_question.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:11:19 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/12 16:29:39 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_question(t_token *token)
{
	if (token->dollar)
	{
		if (token->dollar_word)
		{
			free(token->dollar_word);
			token->dollar_word = 0;
			token->word = make_word_c(token->word, '?');
		}
		else
		{
			if (token->word)
				token->word = make_word_str(token->word, \
				ft_itoa(g_exit_status));
			else
				token->word = ft_itoa(g_exit_status);
		}	
		token->dollar = 0;
	}
	else
		token->word = make_word_c(token->word, '?');
	return (0);
}
