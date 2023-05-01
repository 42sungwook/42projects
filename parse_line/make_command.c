/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:20 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/01 13:31:57 by sungwook         ###   ########.fr       */
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
		while (cmd[i++])
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
	str = ft_strdup(word);
	new_cmd[i] = str;
	new_cmd[i + 1] = 0;
	return (new_cmd);
}

void	make_redirection_line(t_commands *cmds, char *word)
{
	if (cmds->infile->flag)
	{
		cmds->infile->flag = 0;
		cmds->infile->line = ft_strdup(word);
	}
	else if (cmds->outfile->flag)
	{
		cmds->outfile->flag = 0;
		cmds->outfile->line = ft_strdup(word);
	}
	else if (cmds->heredoc->flag)
	{
		cmds->heredoc->flag = 0;
		cmds->heredoc->line = ft_strdup(word);
	}
}

void	make_command(t_commands *cmds, char *word)
{
	char	*temp;

	if (cmds->infile->flag || cmds->outfile->flag || cmds->heredoc->flag)
		make_redirection_line(cmds, word);
	else if (cmds->cmd)
		cmds->cmd = add_cmd(cmds->cmd, word);
	else
	{
		cmds->cmd = (char **)malloc(sizeof(char *) * 2);
		temp = ft_strdup(word);
		cmds->cmd[0] = temp;
		cmds->cmd[1] = 0;
	}
}
