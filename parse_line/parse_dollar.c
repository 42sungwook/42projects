/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:17 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/05 21:12:00 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_dollar(t_token *token)
{
	if (token->dollar == 1)
		find_dollar_word_in_envp(token);
	else if (token->quote == 0 || token->quote == '\"')
		token->dollar = 1;
	else if (token->dollar == 0 && token->quote == '\'')
		token->word = make_word_c(token->word, '$');
	else
		token->dollar = 1;
	token->prev_char = '$';
	return (0);
}
