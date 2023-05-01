/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:58:55 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/01 21:12:36 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	t_envp	*temp;

	temp = token->envp;
	while (temp)
	{
		if (temp->str)
			free(temp->str);
		free(temp);
		temp = temp->next;
	}
	free(token);
}

void	free_line(t_line *line)
{
	t_line	*temp;

	while (line)
	{
		temp = line->next;
		if (line->line)
			free(line->line);
		free(line);
		line = temp;
	}
}

void	free_commands(t_commands *cmds)
{
	t_commands	*temp;

	while (cmds)
	{
		temp = cmds->next;
		if (cmds->cmd)
			free_arr(cmds->cmd);
		free_line(cmds->infile);
		free_line(cmds->outfile);
		free_line(cmds->heredoc);
		free(cmds->fds);
		free(cmds);
		cmds = temp;
	}
}

void	free_everything(t_commands **cmds, t_token *token, char *str)
{
	if (*cmds)
		free_commands(*cmds);
	if (str)
		free(str);
	token->quote = 0;
	token->dollar = 0;
	if (token->dollar_word)
		free(token->dollar_word);
	if (token->word)
		free(token->word);
	token->left_redirection = 0;
	token->right_redirection = 0;
	token->pipe = 0;
	token->command = 0;
	token->prev_char = 0;
	*cmds = init_cmds();
}
