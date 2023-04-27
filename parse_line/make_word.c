// #include "../minishell.h"

// int	make_word(char *curr_word, char *c)
// {
// 	size_t	i;
// 	size_t	word_len;
// 	char	*new_word;

// 	word_len = ft_strlen(curr_word);
// 	word_len++;
// 	new_word = (char *)malloc(sizeof(char) * (word_len + 1));
// 	i = 0;
// 	while (i < word_len)
// 	{
// 		if (i == word_len - 1)
// 			new_word[i] = c;
// 		else
// 			new_word[i] = curr_word[i];
// 		i++;
// 	}
// 	new_word[i] = 0;
// 	if (ft_strlen(c) > 1)
// 		free(c);
// 	free(curr_word);
// 	return (new_word);
// }
