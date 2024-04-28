/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemy2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:58:55 by sungwook          #+#    #+#             */
/*   Updated: 2023/01/03 15:58:56 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	draw_catch_enemy(t_game *g, t_node *temp, size_t time)
{
	if (temp->enemy_alive == 2 || \
		temp->enemy_alive == 4 || \
		temp->enemy_alive == 6)
		put_image_to_window(g, temp->x * 64, temp->y * 64, g->custom.ball);
	else if (temp->enemy_alive == 3)
		put_image_to_window(g, temp->x * 64, temp->y * 64, g->custom.ball2);
	else if (temp->enemy_alive == 5)
		put_image_to_window(g, temp->x * 64, temp->y * 64, g->custom.ball3);
	else if (temp->enemy_alive == 7)
		put_image_to_window(g, temp->x * 64, temp->y * 64, g->custom.ball4);
	if (time % 25 == 0)
		temp->enemy_alive++;
	if (temp->enemy_alive == 8)
		temp->enemy_alive = 0;
}

void	dir_enemy1(t_game *g, t_node *temp, int x, int y)
{
	if (y + 1 < g->map_v.y_size && (temp->map)[y + 1][x] == 0)
	{
		(temp->map)[y + 1][x] = (temp->map)[y][x] + 1;
		enemy_deque_back(g, temp, x, y + 1);
		dir_enemy(g, temp, x, y + 1);
	}
	if (x + 1 < g->map_v.x_size && (temp->map)[y][x + 1] == 0)
	{
		(temp->map)[y][x + 1] = (temp->map)[y][x] + 1;
		enemy_deque_back(g, temp, x + 1, y);
		dir_enemy(g, temp, x + 1, y);
	}
	if (y - 1 > 0 && (temp->map)[y - 1][x] == 0)
	{
		(temp->map)[y - 1][x] = (temp->map)[y][x] + 1;
		enemy_deque_back(g, temp, x, y - 1);
		dir_enemy(g, temp, x, y - 1);
	}
	if (x - 1 > 0 && (temp->map)[y][x - 1] == 0)
	{
		(temp->map)[y][x - 1] = (temp->map)[y][x] + 1;
		enemy_deque_back(g, temp, x - 1, y);
		dir_enemy(g, temp, x - 1, y);
	}
}

void	dir_enemy2(t_game *g, t_node *temp, int x, int y)
{
	if (x - 1 > 0 && (temp->map)[y][x - 1] == 0)
	{
		(temp->map)[y][x - 1] = (temp->map)[y][x] + 1;
		enemy_deque_back(g, temp, x - 1, y);
		dir_enemy(g, temp, x - 1, y);
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
	if (y + 1 < g->map_v.y_size && (temp->map)[y + 1][x] == 0)
	{
		(temp->map)[y + 1][x] = (temp->map)[y][x] + 1;
		enemy_deque_back(g, temp, x, y + 1);
		dir_enemy(g, temp, x, y + 1);
	}
}

void	dir_enemy3(t_game *g, t_node *temp, int x, int y)
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

void	make_enemy_dir(t_node *temp)
{
	static size_t	time;

	if (time % 4 == 0)
		temp->enemy_dir = 3;
	if (time % 4 == 1)
		temp->enemy_dir = 1;
	if (time % 4 == 2)
		temp->enemy_dir = 2;
	if (time % 4 == 3)
		temp->enemy_dir = 0;
	time++;
}
