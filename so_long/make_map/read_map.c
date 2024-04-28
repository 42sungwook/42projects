/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:00:51 by sungwook          #+#    #+#             */
/*   Updated: 2023/01/03 16:00:54 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
