/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanson <chanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:59:16 by chanson           #+#    #+#             */
/*   Updated: 2023/01/02 16:17:04 by chanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static t_map_list	*sl_newlst(char *line)
{
	t_map_list	*new;

	new = (t_map_list *)malloc(sizeof(t_map_list));
	new->line = line;
	new->next = 0;
	return (new);
}

static void	free_maplist(t_map_list *head, t_map_list *list)
{
	list = head;
	while (list == 0)
	{
		list->next = list;
		free(head);
		head = list;
	}
}

static char	**make_map(t_game *game, t_map_list *head)
{
	t_map_list	*list;
	char		**map;
	int			i;

	i = 0;
	list = head;
	map = (char **)malloc(sizeof(char *) * (game->map_v.y_size + 1));
	while (i < game->map_v.y_size)
	{
		map[i] = list->line;
		list = list->next;
		i++;
	}
	map[i] = 0;
	return (map);
}

void	read_map(t_game *game, int fd)
{
	char		*line;
	t_map_list	*head;
	t_map_list	*list;

	head = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		if (!head)
		{
			list = sl_newlst(line);
			head = list;
		}
		else
		{
			list->next = sl_newlst(line);
			list = list->next;
		}
		game->map_v.y_size++;
	}
	game->map = make_map(game, head);
	free_maplist(head, list);
}
