/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:59:18 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/01 21:13:45 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*make_word_str(char *curr_word, char *c)
{
	char	*new_word;

	new_word = ft_strjoin(curr_word, c);
	free(curr_word);
	return (new_word);
}

char	*make_word_c(char *curr_word, char c)
{
	int		i;
	size_t	len;
	char	*new_word;

	len = ft_strlen(curr_word);
	new_word = (char *)malloc(sizeof(char) * (len + 2));
	if (!new_word)
		return (0);
	i = -1;
	if (!curr_word)
		new_word[++i] = c;
	else
	{
		while (curr_word[++i])
			new_word[i] = curr_word[i];
		new_word[i] = c;
	}
	new_word[i + 1] = 0;
	if (curr_word)
		free(curr_word);
	return (new_word);
}
