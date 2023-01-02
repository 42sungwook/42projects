#include "../so_long.h"

static int	map_check_frame(t_game *g, char *line, int idx)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (idx == 0 || idx == g->map_v.y_size - 1)
		{
			if (line[i] != '1' && line[i] != '\n')
				return (0);
		}
		else
		{
			if (i == 0 && line[i] != '1')
				return (0);
			if (i == g->map_v.x_size - 1 && line[i] != '1')
				return (0);
		}
		i++;
	}
	return (1);
}

static void	map_check_cpe(t_game *g, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'C')
			g->map_v.c++;
		if (line[i] == 'P')
			g->map_v.p++;
		if (line[i] == 'E')
			g->map_v.e++;
		i++;
	}
}

int	map_check(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while ((g->map)[i])
	{
		j = 0;
		map_check_cpe(g, (g->map)[i]);
		while ((g->map)[i][j] != '\n' && (g->map)[i][j] != 0)
			j++;
		if (g->map_v.x_size == 0 && i == 0)
			g->map_v.x_size = j;
		else
		{
			if (g->map_v.x_size != j || map_check_frame(g, (g->map)[i], i) == 0)
				return (0);
		}
		i++;
	}
	if (g->map_v.c < 1 || g->map_v.e != 1 || g->map_v.p != 1)
		return (0);
	if (g->map_v.x_size < 5 || g->map_v.y_size < 5)
		return (2);
	return (1);
}

void	check_valid(t_game	*g)
{
	int	n;

	n = map_check(g);
	if (n == 0)
	{
		write(1, "ERROR: MAP IS NOT VALID\n", 24);
		exit(0);
	}
	if (n == 2)
	{
		write(1, "ERROR: MAP SIZE ERROR\n", 22);
		exit(0);
	}
	if (map_check_way(g) == 0)
	{
		write(1, "ERROR: MAP HAS NO WAY OUT\n", 26);
		exit(0);
	}
}