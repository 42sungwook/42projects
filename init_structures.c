/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:58:47 by daijeong          #+#    #+#             */
/*   Updated: 2023/04/28 22:10:13 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ps_addlist(char *str)
{
	t_envp	*envp_list;

	envp_list = (t_envp *)malloc(sizeof(t_envp));
	envp_list->str = ft_strdup(str);
	return (envp_list);
}

void	init_envp(t_token *token, char **envp)
{
	t_envp	*envp_list;
	t_envp	*temp;
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (!(envp_list))
		{
			temp = ps_addlist(envp[i]);
			envp_list = temp;
		}
		else
		{
			temp->next = ps_addlist(envp[i]);
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
	token->command = 0;
	token->heredoc = 0;
	token->left_redirection = 0;
	token->right_redirection = 0;
	token->word = 0;
	token->dollar_word = 0;
	token->prev_char = 0;
	return (token);
}

t_commands	*init_cmds(void)
{
	t_commands	*cmds;

	cmds = malloc(sizeof(t_commands));
	cmds->infile = 0;
	cmds->outfile = 0;
	cmds->infile_fd = -1;
	cmds->outfile_fd = -1;
	cmds->cmd = 0;
	cmds->exit_code = 0;
	cmds->next = 0;
	return (cmds);
}

