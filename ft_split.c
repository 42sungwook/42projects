/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:42:23 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/16 17:07:16 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_malloc_ok(int len, int count)
{
	char	*word;
	char	**words;

	if (count == 0)
		return (1);
	words = (char **)malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (0);
	word = (char *)malloc(sizeof(char) * len);
	if (!word)
	{
		free (words);
		return (0);
	}
	free (word);
	return (1);
}

int	num_of_str(char const *str, char c)
{
	int	i;
	int	j;
	int	count;
	int	tot_len;

	i = 0;
	count = 0;
	tot_len = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			j = 0;
			while (str[i + j] && str[i + j] != c)
				j++;
			count++;
			tot_len += j;
			i += j;
		}
		else
			i++;
	}
	if (ft_malloc_ok(tot_len + count, count) == 0)
		return (-1);
	return (count);
}

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*new_str;

	i = 0;
	new_str = (char *)malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return (0);
	while (i < n)
	{
		new_str[i] = s1[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

void	ft_cutstr(char const *s, char **split_str, char c)
{
	int	i;
	int	len;
	int	start;

	i = -1;
	len = 0;
	start = 0;
	while (s[++i])
	{
		if (s[i] == c)
		{
			if (len != 0)
			{
				*split_str++ = ft_strndup(s + start, len);
				if (split_str == 0)
					return ;
				len = 0;
			}
			continue ;
		}
		if (len == 0)
			start = i;
		len++;
	}
	*split_str++ = ft_strndup(s + start, len);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		count;
	char	**split_str;

	i = 0;
	count = num_of_str(s, c);
	split_str = (char **)malloc(sizeof(char *) * (count + 1));
	if (!split_str)
		return (0);
	ft_cutstr(s, split_str, c);
	split_str[count] = 0;
	return (split_str);
}
