#include "pipex.h"

static int	num_of_str(char const *str, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			j = 0;
			while (str[i + j] && str[i + j] != c)
				j++;
			count++;
			i += j;
		}
		else
			i++;
	}
	return (count);
}

static void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static void	ft_make_str(char *str, char const *s, int end_of_str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		str[i] = s[end_of_str - len + i];
		i++;
	}
	str[i] = 0;
}

static char	**ft_cutstr(char const *s, char c, char **split_str, int count)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i] && j < count)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			len++;
		}
		split_str[j] = (char *)malloc(sizeof(char) * (len + 1));
		if (!split_str[j])
			return (0);
		ft_make_str(split_str[j], s, i, len);
		len = 0;
		j++;
	}
	split_str[j] = 0;
	return (split_str);
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
	if (ft_cutstr(s, c, split_str, count) == 0)
	{
		ft_free(split_str);
		return (0);
	}
	return (split_str);
}