/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:20 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/04 19:43:34 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_cmd(char **cmd, char *word)
{
	int		i;
	char	**new_cmd;
	char	*str;

	i = 0;
	if (cmd)
	{
		while (cmd[i++])
			;
	}
	new_cmd = (char **)malloc(sizeof(char *) * (i + 2));
	if (!(new_cmd))
		return (0);
	i = -1;
	if (cmd)
	{
		while (cmd[++i])
			new_cmd[i] = cmd[i];
	}
	else
		i = 0;
	if (!word)
		str = 0;
	else
		str = ft_strdup(word);
	new_cmd[i] = str;
	new_cmd[i + 1] = 0;
	return (new_cmd);
}

void	make_redirection_line(t_commands *cmds, t_token	*token)
{
	token->left_redirection = 0;
	token->right_redirection = 0;
	if (cmds->infile_end->flag == 1)
	{
		cmds->read_heredoc = INFILE_END;
		cmds->infile_end->line = ft_strdup(token->word);
		cmds->infile_end->next = init_line();
		cmds->infile_end = cmds->infile_end->next;
	}
	else if (cmds->infile_end->flag == 2)
	{
		cmds->heredoc_end->flag = 1;
		cmds->infile_end->flag = 0;
		cmds->read_heredoc = HEREDOC_END;
		cmds->heredoc_end->line = ft_strdup(token->word);
		cmds->heredoc_end->next = init_line();
		cmds->heredoc_end = cmds->heredoc_end->next;
	}
	else if (cmds->outfile_end->flag)
	{
		cmds->outfile_end->line = ft_strdup(token->word);
		cmds->outfile_end->next = init_line();
		cmds->outfile_end = cmds->outfile_end->next;
	}
}

void	make_command(t_commands *cmds, t_token *token)
{
	char	*temp;

	if (cmds->infile_end->flag || cmds->outfile_end->flag)
		make_redirection_line(cmds, token);
	else if (cmds->cmd)
		cmds->cmd = add_cmd(cmds->cmd, token->word);
	else
	{
		cmds->cmd = (char **)malloc(sizeof(char *) * 2);
		temp = ft_strdup(token->word);
		cmds->cmd[0] = temp;
		cmds->cmd[1] = 0;
	}
}
