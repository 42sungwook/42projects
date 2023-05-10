/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:22 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/10 22:00:40 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	found_dollar_word_in_envp(t_token *token, t_envp *envp_temp, int j)
{
	char	*temp;

	if (!token->word)
		temp = ft_strdup(&envp_temp->str[j + 1]);
	else
		temp = ft_strjoin(token->word, &envp_temp->str[j + 1]);
	if (token->word)
		free(token->word);
	free(token->dollar_word);
	token->dollar_word = 0;
	token->dollar = 0;
	token->word = temp;
	return ;
}

void	find_dollar_word_in_envp(t_token *token)
{
	int		j;
	int		dollar_word_len;
	t_envp	*envp_temp;

	envp_temp = token->envp;
	dollar_word_len = ft_strlen(token->dollar_word);
	while (envp_temp)
	{
		j = -1;
		while (++j < dollar_word_len)
		{
			if (envp_temp->str[j] != token->dollar_word[j])
				break ;
		}
		if (j != dollar_word_len)
		{
			envp_temp = envp_temp->next;
			continue ;
		}
		if (j == dollar_word_len && envp_temp->str[j] == '=')
			found_dollar_word_in_envp(token, envp_temp, j);
		envp_temp = envp_temp->next;
	}
}

void	end_of_word(t_commands *cmds, t_token *token, char c)
{
	if (token->dollar == 1 && token->quote == 0)
	{
		find_dollar_word_in_envp(token);
		token->dollar = 0;
	}
	if ((c == 0 && (token->quote == '\'' || token->quote == '\"')) || \
		(token->quote == 0 && token->dollar == 0))
	{
		if (token->word)
		{
			make_command(cmds, token);
			free(token->word);
			token->word = 0;
		}
	}
	token->prev_char = c;
	if (c == '|')
		return ;
	else if (token->quote != 0 && token->dollar == 0)
		token->word = make_word_c(token->word, c);
	else if (token->dollar == 1 && token->quote == 1)
		find_dollar_word_in_envp(token);
}
