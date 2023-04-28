/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:22 by daijeong          #+#    #+#             */
/*   Updated: 2023/04/28 17:24:49 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_dollar_word_in_envp(t_token *token)
{
	int		i;
	int		j;
	int		dollar_word_len;
	char	*temp;

	i = -1;
	dollar_word_len = ft_strlen(&(token->dollar_word[token->dollar_index]));
	while (token->envp[++i])
	{
		j = -1;
		while (++j < dollar_word_len)
		{
			if (token->envp[i][j] != token->dollar_word[j])
				break ;
		}
		if (j == dollar_word_len && token->envp[i][j] == '=')
		{
			temp = ft_strjoin(token->word, &(token->envp[i][j + 1]));
			printf("temp: %s\n", temp);
			printf("token->envp: %s\n", &(token->envp[i][j + 1]));
			free(token->word);
			token->word = temp;
			return (token->dollar_word);
		}
	}
	return (NULL);
}

int	end_of_word(t_commands *cmds, t_token *token, char c)
{
	if (token->quote == 0 && token->dollar == 0)
	{
		if (token->word)
		{
			make_command(cmds, token->word);
			free(token->word);
			token->word = NULL;
		}
	}
	else if (token->quote != 0 && token->dollar == 0)
		token->word = make_word_c(token->word, c);
	else if (token->dollar == 1 && token->quote == 1)
		token->word = make_word_str(token->word, find_dollar_word_in_envp(token));//확인 필요
	token->prev_char = c;
	return (0);
}
