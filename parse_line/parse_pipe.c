/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:10 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/17 21:26:31 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_pipe(t_commands **cmds, t_token *token)
{
	end_of_word(*cmds, token, '|');
	if (!(*cmds)->cmd)
		return (1);
	(*cmds)->next = init_cmds();
	*cmds = (*cmds)->next;
	token->pipe++;
	token->prev_char = '|';
	return (0);
}
