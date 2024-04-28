/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:43:59 by sungwook          #+#    #+#             */
/*   Updated: 2023/04/15 15:32:14 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	gnl_find(char *buff)
{
	size_t	i;

	i = 0;
	if (!buff)
		return (0);
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != 0)
		i++;
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2, size_t i, size_t j)
{
	size_t	len;
	size_t	s1_len;
	char	*join;

	s1_len = gnl_strlen(s1);
	len = s1_len + gnl_strlen(s2);
	if (s1_len > len)
	{
		free(s1);
		return (0);
	}
	join = (char *)malloc(sizeof(char) * (len + 1));
	while (i < s1_len)
	{
		join[i] = s1[i];
		i++;
	}
	while (i + j < len)
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = 0;
	free(s1);
	return (join);
}
