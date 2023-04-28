/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:11 by daijeong          #+#    #+#             */
/*   Updated: 2023/04/28 17:08:08 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_double_quote(t_token *token)
{
	if (token->quote == 0 && token->dollar == 0) // quote가 0이고 dollar가 0이면 즉, "가 아직 닫히지 않았을 경우 
		token->quote = '\"';
	else if (token->quote == '\"' && token->dollar == 0) // quote가 1이고 dollar가 0이면 즉, "가 닫혔을 경우
		token->quote = 0;
	else if ((token->quote == '\"' && token->dollar == 1) || (token->quote == 0 && token->dollar == 1)) // quote가 1이고 dollar가 1이면 즉, "가 닫혔고 $가 있을 경우
		token->word = make_word_str(token->word, find_dollar_word_in_envp(token));//확인 필요
	token->prev_char = '\"';
	return (0);
}