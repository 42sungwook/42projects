/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_user.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:59:29 by sungwook          #+#    #+#             */
/*   Updated: 2023/01/03 15:59:30 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	_draw_user_x(t_game *g)
{
	int			s;
	static int	cnt;

	s = g->user.pre_x;
	if (g->user.pre_x < g->user.x)
	{
		if (cnt % 4 == 0)
			put_image_to_window(g, s, g->user.y - 10, g->user.user_e1);
		else
			put_image_to_window(g, s, g->user.y - 10, g->user.user_e2);
		g->user.pre_x += 4;
	}
	if (g->user.pre_x > g->user.x)
	{
		if (cnt % 4 == 0)
			put_image_to_window(g, s, g->user.y - 10, g->user.user_w1);
		else
			put_image_to_window(g, s, g->user.y - 10, g->user.user_w2);
		g->user.pre_x -= 4;
	}
	if (cnt++ == 15)
	{
		cnt = 0;
		g->key_sign = 0;
	}
}

static void	_draw_user_y(t_game *g)
{
	int			s;
	static int	cnt_2;

	s = g->user.pre_y - 10;
	if (g->user.pre_y < g->user.y)
	{
		if (cnt_2 % 4 == 0)
			put_image_to_window(g, g->user.x, s, g->user.user_s1);
		else
			put_image_to_window(g, g->user.x, s, g->user.user_s2);
		g->user.pre_y += 4;
	}
	if (g->user.pre_y > g->user.y)
	{
		if (cnt_2 % 4 == 0)
			put_image_to_window(g, g->user.x, s, g->user.user_n1);
		else
			put_image_to_window(g, g->user.x, s, g->user.user_n2);
		g->user.pre_y -= 4;
	}
	if (cnt_2++ == 15)
	{
		cnt_2 = 0;
		g->key_sign = 0;
	}
}

void	draw_user(t_game *g)
{
	int	x;
	int	y;

	x = g->user.pre_x;
	y = g->user.pre_y - 10;
	if (x == g->user.x && y == g->user.y - 10)
		put_image_to_window(g, x, y, dir_img(g, g->user.d));
	else
	{
		if (x != g->user.x)
			_draw_user_x(g);
		else
			_draw_user_y(g);
	}
}
