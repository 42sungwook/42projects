/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_single_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:00 by daijeong          #+#    #+#             */
/*   Updated: 2023/04/28 16:53:04 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_single_quote(t_token *token)
{
	if (token->quote == 0)
		token->quote = '\'';
	else if (token->quote == '\'')
		token->quote = 0;
	token->prev_char = '\'';
	return (0);
}
