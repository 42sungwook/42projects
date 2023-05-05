/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:58:55 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/05 14:42:00 by sungwook         ###   ########.fr       */
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

void	free_everything(t_commands *cmds, t_token *token, char *str)
{
	t_commands	*temp;

	temp = cmds;
	while (temp)
	{
		if (temp->infile)
			free_line(temp->infile);
		if (temp->outfile)
			free_line(temp->outfile);
		if (temp->heredoc)
			free_line(temp->heredoc);
		if (temp->fds)
			free(temp->fds);
		if (temp->cmd)
			free_arr(temp->cmd);
		temp = temp->next;
	}
	while (cmds)
	{
		temp = cmds->next;
		free(cmds);
		cmds = temp;
	}
	if (str)
		free(str);
	token->quote = 0;
	token->dollar = 0;
	if (token->dollar_word)
	{
		free(token->dollar_word);
		token->dollar_word = 0;
	}
	if (token->word)
	{
		free(token->word);
		token->word = 0;
	}
	token->left_redirection = 0;
	token->right_redirection = 0;
	token->pipe = 0;
	token->prev_char = 0;
}
