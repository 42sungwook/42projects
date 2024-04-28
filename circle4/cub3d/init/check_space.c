#include "../srcs/cub3d.h"

int	check_space(char *one_line, char *buff)
{
	int	i;

	i = 0;
	if (one_line[0] == 0 && buff[0] == '\n')
	{
		free(buff);
		return (1);
	}
	while (buff[i])
	{
		if (buff[i] == '0' || buff[i] == '1')
			return (0);
		else if (buff[i] == '\n' && one_line[0] != 0)
			return (0);
		i++;
	}
	return (1);
}