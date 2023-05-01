/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:07 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/01 16:56:25 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_left_redirection(t_commands *cmds, t_token *token)
{
	if ((token->left_redirection == 0 || token->left_redirection == 1) \
		&& token->right_redirection == 0)
	{
		token->left_redirection++;
		cmds->infile->flag++;
		if (cmds->infile->flag == 2)
		{
			cmds->infile->flag = 0;
			cmds->heredoc->flag = 1;
		}
	}
	else
		token->exit_status = 258;
}

void	parse_right_redirection(t_commands *cmds, t_token *token)
{
	if ((token->right_redirection == 0 || token->right_redirection == 1) \
		&& token->left_redirection == 0)
	{
		token->right_redirection++;
		cmds->outfile->flag++;
	}
	else
		token->exit_status = 258;
}

int	parse_redirection(t_commands *cmds, t_token *token, char c)
{
	if (token->word)
	{
		make_command(cmds, token);
		free(token->word);
		token->word = 0;
	}
	if (c == '<')
		parse_left_redirection(cmds, token);
	else if (c == '>')
		parse_right_redirection(cmds, token);
	return (0);
}
// <<
// <
// >
// >>
//<<<
//>>>
//<a <b <c
//<a <<b <c cat | << d
//syntax error: 258