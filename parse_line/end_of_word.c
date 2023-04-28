/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:22 by daijeong          #+#    #+#             */
/*   Updated: 2023/04/28 20:11:14 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_dollar_word_in_envp(t_token *token)
{
	int		i;
	int		j;
	int		dollar_word_len;
	char	*temp;

	i = -1;
	dollar_word_len = ft_strlen(token->dollar_word);
	while (token->envp[++i])
	{
		j = -1;
		while (++j < dollar_word_len)
		{
			if (token->envp[i][j] != token->dollar_word[j])
				break ;
		}
		if (j != dollar_word_len)
			continue ;
		if (j == dollar_word_len && token->envp[i][j] == '=')
		{
			if (!token->word)
				temp = ft_strdup(token->envp[i] + j + 1);
			else
				temp = ft_strjoin(token->word, token->envp[i] + j + 1);
			if (token->word)
				free(token->word);
			free(token->dollar_word);
			token->dollar_word = 0;
			token->dollar = 0;
			token->word = temp;
			return ;
		}
	}
}

int	end_of_word(t_commands *cmds, t_token *token, char c)
{
	if (token->dollar == 1 && token->quote == 0)
	{
		find_dollar_word_in_envp(token);
		token->dollar = 0;
	}
	if (token->quote == 0 && token->dollar == 0)
	{
		if (token->word)
		{
			make_command(cmds, token->word);
			free(token->word);
			token->word = 0;
		}
	}
	else if (token->quote != 0 && token->dollar == 0)
		token->word = make_word_c(token->word, c);
	else if (token->dollar == 1 && token->quote == 1)
		find_dollar_word_in_envp(token);
	token->prev_char = c;
	return (0);
}
