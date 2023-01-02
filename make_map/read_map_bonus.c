/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanson <chanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:59:16 by chanson           #+#    #+#             */
/*   Updated: 2023/01/02 21:28:17 by chanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static void	make_map2(char **map, char *line, int i, int j)
{
	map[i] = (char *)malloc(sizeof(char) * (j + 1));
	map[i][j] = 0;
	j--;
	while (j >= 0)
	{
		map[i][j] = line[j];
		j--;
	}
}

static char	**make_map(t_game *game, int fd)
{
	char	**map;
	char	*line;
	int		i;
	int		j;

	i = 0;
	map = (char **)malloc(sizeof(char *) * (game->map_v.y_size + 1));
	while (i < game->map_v.y_size)
	{
		line = get_next_line(fd);
		j = 0;
		while (line[j])
			j++;
		make_map2(map, line, i, j);
		free(line);
		i++;
	}
	map[i] = 0;
	return (map);
}

void	read_map(t_game *game)
{
	char		*line;
	int			fd;

	fd = open(game->addr, O_RDONLY);
	if (fd == -1)
	{
		perror("file error");
		exit (0);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		game->map_v.y_size++;
		free(line);
	}
	close(fd);
	fd = open(game->addr, O_RDONLY);
	game->map = make_map(game, fd);
	close(fd);
}
