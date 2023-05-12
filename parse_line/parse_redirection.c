/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:07 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/12 21:39:50 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_left_redirection(t_commands *cmds, t_token *token)
{
	if ((token->left_redirection == 0 || token->left_redirection == 1) \
		&& token->right_redirection == 0)
	{
		token->left_redirection++;
		cmds->infile_end->flag++;
	}
	else
		g_exit_status = SYNTAX_ERROR;
}

void	parse_right_redirection(t_commands *cmds, t_token *token)
{
	if ((token->right_redirection == 0 || token->right_redirection == 1) \
		&& token->left_redirection == 0)
	{
		token->right_redirection++;
		cmds->outfile_end->flag++;
	}
	else
		g_exit_status = SYNTAX_ERROR;
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
