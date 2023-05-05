/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:58:47 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/05 14:42:09 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line	*init_line(void)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	line->line = 0;
	line->flag = 0;
	line->next = 0;
	return (line);
}

t_envp	*envp_addlist(char *str)
{
	t_envp	*envp_list;

	envp_list = (t_envp *)malloc(sizeof(t_envp));
	envp_list->str = ft_strdup(str);
	envp_list->next = 0;
	return (envp_list);
}

void	init_envp(t_token *token, char **envp)
{
	t_envp	*envp_list;
	t_envp	*temp;
	size_t	i;

	i = 0;
	envp_list = 0;
	while (envp[i])
	{
		if (!(envp_list))
		{
			temp = envp_addlist(envp[i]);
			envp_list = temp;
		}
		else
		{
			temp->next = envp_addlist(envp[i]);
			temp = temp->next;
		}
		i++;
	}
	token->envp = envp_list;
}

t_token	*init_token(char **envp)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	init_envp(token, envp);
	token->quote = 0;
	token->dollar = 0;
	token->pipe = 0;
	token->left_redirection = 0;
	token->right_redirection = 0;
	token->word = 0;
	token->dollar_word = 0;
	token->exit_status = 0;
	token->prev_char = 0;
	return (token);
}

t_commands	*init_cmds(void)
{
	t_commands	*cmds;

	cmds = malloc(sizeof(t_commands));
	cmds->infile = init_line();
	cmds->infile_end = cmds->infile;
	cmds->outfile = init_line();
	cmds->outfile_end = cmds->outfile;
	cmds->heredoc = init_line();
	cmds->heredoc_end = cmds->heredoc;
	cmds->read_heredoc = 0;
	cmds->cmd = 0;
	cmds->fds = 0;
	cmds->next = 0;
	return (cmds);
}

