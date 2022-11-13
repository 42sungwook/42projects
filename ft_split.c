/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:42:23 by sungwook          #+#    #+#             */
/*   Updated: 2022/11/13 21:01:51 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	start;

	i = -1;
	j = -1;
	len = 0;
	start = 0;
	while (++i < ft_strlen(s))
	{
		if (s[i] == c)
		{
			split_str[++j] = ft_strndup(&s[start], len);
			start += len + 1;
			len = 0;
			continue ;
		}
		len++;
	}
	split_str[++j] = 0;
	return ;
}

int	ft_free_split(char **split_str, int len)
{
	int	i;

	i = 0;
	while (len-- > 0)
	{
		if (split_str[len - 1] == 0)
		{
			while (i < len)
			{
				free (split_str[i]);
				i++;
			}
			return (0);
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	char	**split_str;

	i = 0;
	len = 0;
	split_str = (char **)malloc(sizeof(char *) * (ft_strlen(s) + 1));
	if (!split_str)
		return (0);
	ft_cutstr(s, split_str, c);
	while (s[i] != 0)
	{
		if (s[i] == c)
			len++;
		i++;
	}
	if (ft_free_split(split_str, len) == 0)
		return (0);
	return (split_str);
}
