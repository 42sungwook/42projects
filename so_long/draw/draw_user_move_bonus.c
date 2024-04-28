/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_user_move_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanson <chanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:00:13 by chanson           #+#    #+#             */
/*   Updated: 2023/01/02 16:16:30 by chanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	*dir_img(t_game *g, int d)
{
	if (d == 0)
		return (g->user.user_e0);
	if (d == 1)
		return (g->user.user_w0);
	if (d == 2)
		return (g->user.user_n0);
	return (g->user.user_s0);
}

void	draw_move_e(t_game *g)
{
	int	x;
	int	y;

	if (g->start == 0)
		return ;
	x = (g->user.x) / 64;
	y = (g->user.y) / 64;
	x++;
	if (x < g->map_v.x_size - 1 && (g->map1)[y][x] != MAP_WALL)
	{
		g->key_sign = 1;
		g->user.x += 64;
		g->user.d = 0;
		g->user.move++;
		draw_user(g);
	}
}

void	draw_move_w(t_game *g)
{
	int	x;
	int	y;

	if (g->start == 0)
		return ;
	x = (g->user.x) / 64;
	y = (g->user.y) / 64;
	x--;
	if (x > 0 && (g->map1)[y][x] != MAP_WALL)
	{
		g->key_sign = 1;
		g->user.x -= 64;
		g->user.d = 1;
		g->user.move++;
		draw_user(g);
	}
}

void	draw_move_n(t_game *g)
{
	int	x;
	int	y;

	if (g->start == 0)
		return ;
	x = (g->user.x) / 64;
	y = (g->user.y) / 64;
	y--;
	if (y > 0 && (g->map1)[y][x] != MAP_WALL)
	{
		g->key_sign = 1;
		g->user.y -= 64;
		g->user.d = 2;
		g->user.move++;
		draw_user(g);
	}
}

void	draw_move_s(t_game *g)
{
	int	x;
	int	y;

	if (g->start == 0)
		return ;
	x = (g->user.x) / 64;
	y = (g->user.y) / 64;
	y++;
	if (y < g->map_v.y_size - 1 && (g->map1)[y][x] != MAP_WALL)
	{
		g->key_sign = 1;
		g->user.y += 64;
		g->user.d = 3;
		g->user.move++;
		draw_user(g);
	}
}
