/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:17 by daijeong          #+#    #+#             */
/*   Updated: 2023/04/28 17:14:04 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_dollar(t_token *token)
{
	if (token->dollar == 1)
	{
		token->word = make_word_str(token->word, find_dollar_word_in_envp(token));//확인 필요
		token->dollar_index = ft_strlen(token->word);
	}
	else if (token->quote == 0 || token->quote == '\"')
	{
		token->dollar = 1;
		token->dollar_index = ft_strlen(token->word);
	}
	else
		make_word_c(token->word, '$');
	token->prev_char = '$';

	return (0);
}
