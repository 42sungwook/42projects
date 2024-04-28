/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_question.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:11:19 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/25 19:52:19 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_dollar_question(t_token *token)
{
	char	*status;

	status = ft_itoa(g_exit_status);
	if (token->word)
	{
		token->word = make_word_str(token->word, status);
		free(status);
	}
	else
		token->word = status;
}

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
			parse_dollar_question(token);
		token->dollar = 0;
	}
	else
		token->word = make_word_c(token->word, '?');
	token->prev_char = '?';
	return (0);
}
