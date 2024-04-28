#include "../srcs/cub3d.h"

int	ft_free(char *str)
{
	if (!str)
		return (0);
	free(str);
	str = 0;
	return (1);
}

void	free_chars(char **chars)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		free(chars[i]);
		i++;
	}
	free(chars);
	chars = 0;
}

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}