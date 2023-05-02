/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:10 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/02 12:03:56 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_commands	*parse_pipe(t_commands *cmds, t_token *token)
{
	end_of_word(cmds, token, '|');
	cmds->next = init_cmds();
	cmds = cmds->next;
	token->pipe++;
	return (cmds);
}
