#include "../minishell.h"

char	*make_word_str(char *curr_word, char *c)
{
	size_t	i;
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
