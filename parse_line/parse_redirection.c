/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:07 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/17 21:29:33 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_left_redirection(t_commands *cmds, t_token *token)
{
	if ((token->left_redirection == 0 || token->left_redirection == 1) \
		&& token->right_redirection == 0)
	{
		token->left_redirection++;
		cmds->infile_end->flag++;
		return (0);
	}
	else
		return (1);
}

int	parse_right_redirection(t_commands *cmds, t_token *token)
{
	if ((token->right_redirection == 0 || token->right_redirection == 1) \
		&& token->left_redirection == 0)
	{
		token->right_redirection++;
		cmds->outfile_end->flag++;
	}
	else
		return (1);
	return (0);
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
	{
		if (token->prev_char == '>')
			return (1);
		token->prev_char = c;
		return (parse_left_redirection(cmds, token));
	}
	else if (c == '>')
	{
		if (token->prev_char == '<')
			return (1);
		token->prev_char = c;
		return (parse_right_redirection(cmds, token));
	}
	return (0);
}
