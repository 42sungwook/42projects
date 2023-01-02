/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemy_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanson <chanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:59:56 by chanson           #+#    #+#             */
/*   Updated: 2023/01/02 21:10:42 by chanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	enemy_deque_back(t_game *g, t_node *temp, int x, int y)
{
	int	i;
	int	j;

	i = g->user.x / 64;
	j = g->user.y / 64;
	if ((temp->map)[j][i] != 0)
		return ;
	deque_back(temp->way, x, y);
}

void	dir_enemy0(t_game *g, t_node *temp, int x, int y)
{
	if (y + 1 < g->map_v.y_size && (temp->map)[y + 1][x] == 0)
	{
		(temp->map)[y + 1][x] = (temp->map)[y][x] + 1;
		enemy_deque_back(g, temp, x, y + 1);
		dir_enemy(g, temp, x, y + 1);
	}
	if (y - 1 > 0 && (temp->map)[y - 1][x] == 0)
	{
		(temp->map)[y - 1][x] = (temp->map)[y][x] + 1;
		enemy_deque_back(g, temp, x, y - 1);
		dir_enemy(g, temp, x, y - 1);
	}
	if (x + 1 < g->map_v.x_size && (temp->map)[y][x + 1] == 0)
	{
		(temp->map)[y][x + 1] = (temp->map)[y][x] + 1;
		enemy_deque_back(g, temp, x + 1, y);
		dir_enemy(g, temp, x + 1, y);
	}
	if (x - 1 > 0 && (temp->map)[y][x - 1] == 0)
	{
		(temp->map)[y][x - 1] = (temp->map)[y][x] + 1;
		enemy_deque_back(g, temp, x - 1, y);
		dir_enemy(g, temp, x - 1, y);
	}
}

void	dir_enemy(t_game *g, t_node *temp, int x, int y)
{
	int	user_x;
	int	user_y;

	user_x = (g->user.x) / 64;
	user_y = (g->user.y) / 64;
	if (x == (g->user.x / 64) && y == (g->user.y / 64))
	{
		deque_back(temp->way, x, y);
		return ;
	}
	if ((temp->map)[user_y][user_x] == 0)
	{
		if (temp->enemy_dir == 0)
			dir_enemy0(g, temp, x, y);
		if (temp->enemy_dir == 1)
			dir_enemy1(g, temp, x, y);
		if (temp->enemy_dir == 2)
			dir_enemy2(g, temp, x, y);
		if (temp->enemy_dir == 3)
			dir_enemy3(g, temp, x, y);
	}
	if ((temp->map)[user_y][user_x] == 0)
		delete_back_deque(temp->way);
}

static void	move_enemy(t_game *g, t_node *temp)
{
	int	x;
	int	y;

	if (temp->way == 0 || temp->way->cnt == 0)
	{
		ft_free(temp->map, g);
		temp->map = 0;
		delete_deque(temp->way);
		temp->map = dup_arr(g->map1, g->map_v.x_size, g->map_v.y_size);
		make_enemy_map(temp->map, g);
		temp->way = new_deque();
		deque_back(temp->way, temp->x, temp->y);
		(temp->map)[temp->y][temp->x] = 1;
		dir_enemy(g, temp, temp->x, temp->y);
	}
	x = temp->way->front->x;
	y = temp->way->front->y;
	temp->x = x;
	temp->y = y;
	put_image_to_window(g, temp->x * 64, temp->y * 64, g->custom.enemy);
	delete_front_deque(temp->way);
}

void	draw_enemy(t_game *g)
{
	static size_t	time;
	t_node			*temp;
	size_t			i;

	time++;
	i = 0;
	temp = g->enemy_list->front;
	while (temp)
	{
		if (temp->enemy_alive == 1)
		{
			i++;
			put_image_to_window(g, temp->x * 64, temp->y * 64, g->custom.enemy);
			if (time % 20 == 0)
			{
				make_enemy_dir(temp);
				move_enemy(g, temp);
			}
		}
		else if (temp->enemy_alive > 1)
			draw_catch_enemy(g, temp, time);
		temp = temp->next;
	}
	if (time == 1600)
		time = 0;
}
