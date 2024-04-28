/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_way_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanson <chanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:59:02 by chanson           #+#    #+#             */
/*   Updated: 2023/01/02 16:17:00 by chanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static int	check_collect_possible(t_game *g)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (g->map[i])
	{
		j = 0;
		while ((g->map)[i][j] != '\n' && (g->map)[i][j] != 0)
		{
			if ((g->map)[i][j] == 'C')
			{
				if ((g->map2)[i][j] == 0)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static void	make_site(t_game *g, int x, int y)
{
	while (y++ < g->map_v.y_size - 1)
	{
		x = -1;
		while (x++ < g->map_v.x_size - 1)
		{
			if ((g->map2)[y][x] == MAP_EXIT)
			{
				g->custom.x = x;
				g->custom.y = y;
			}
			else if ((g->map2)[y][x] == MAP_USER)
			{
				g->user.x = x;
				g->user.y = y;
			}
			if ((g->map2)[y][x] == MAP_COLLECTABLE)
				g->custom.cnt++;
			if ((g->map2)[y][x] != MAP_WALL)
				(g->map2)[y][x] = 0;
		}
	}
}

static void	ft_case(int **arr, t_game *g, t_deque *deque, int c)
{
	int	x;
	int	y;

	x = g->user.x;
	y = g->user.y;
	if (c == 1)
	{
		arr[y][x + 1] = arr[y][x] + 1;
		deque_back(deque, x + 1, y);
	}
	if (c == 2)
	{
		arr[y][x - 1] = arr[y][x] + 1;
		deque_back(deque, x - 1, y);
	}
	if (c == 3)
	{
		arr[y + 1][x] = arr[y][x] + 1;
		deque_back(deque, x, y + 1);
	}
	if (c == 4)
	{
		arr[y - 1][x] = arr[y][x] + 1;
		deque_back(deque, x, y - 1);
	}
}

static void	map_find_way(t_game *g)
{
	t_node	*node;
	t_deque	*deque;

	g->user.pre_x = g->user.x;
	g->user.pre_y = g->user.y;
	node = new_node(g->user.x, g->user.y);
	deque = new_deque();
	deque_add_back(deque, node);
	while (deque->cnt)
	{
		g->user.x = deque->front->x;
		g->user.y = deque->front->y;
		if (g->user.x + 1 < g->map_v.x_size \
			&& (g->map2)[g->user.y][g->user.x + 1] == 0)
			ft_case(g->map2, g, deque, 1);
		if (g->user.x - 1 >= 0 && (g->map2)[g->user.y][g->user.x - 1] == 0)
			ft_case(g->map2, g, deque, 2);
		if (g->user.y + 1 < g->map_v.y_size \
			&& (g->map2)[g->user.y + 1][g->user.x] == 0)
			ft_case(g->map2, g, deque, 3);
		if (g->user.y - 1 >= 0 && (g->map2)[g->user.y - 1][g->user.x] == 0)
			ft_case(g->map2, g, deque, 4);
		delete_front_deque(deque);
	}
	delete_deque(deque);
}

int	map_check_way(t_game *g)
{
	int	x;
	int	y;

	y = -1;
	x = -1;
	g->map1 = make_int_map(g, 0, 0);
	g->map2 = make_int_map(g, 0, 0);
	make_site(g, x, y);
	map_find_way(g);
	if ((g->map2)[g->custom.y][g->custom.x] == 0 || check_collect_possible(g))
		return (0);
	g->map_v.total_move = (g->map2)[g->custom.y][g->custom.x];
	return (1);
}
