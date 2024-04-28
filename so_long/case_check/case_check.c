/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:58:26 by sungwook          #+#    #+#             */
/*   Updated: 2023/01/03 15:58:27 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	game_restart(t_game *g)
{
	ft_free(g->map1, g);
	g->map1 = make_int_map(g, 0, 0);
	find_site(g->map1, g);
	g->map_v.total_move = (g->map2)[g->custom.y][g->custom.x];
	g->reset = 0;
	g->user.x = g->user.x * 64;
	g->user.y = g->user.y * 64;
	g->user.pre_x = g->user.x;
	g->user.pre_y = g->user.y;
	g->user.move = 0;
	g->key_sign = 0;
	g->user.d = 3;
	g->start = 0;
	return (0);
}

void	case_eat_collectable(t_game *g, int x, int y)
{
	g->map_v.total_move += 3;
	g->custom.cnt--;
	(g->map1)[y][x] = 0;
}

void	case_enter_escape(t_game *g)
{
	mlx_clear_window(g->mlx, g->win);
	g->key_sign = 0;
	g->reset = 1;
	mlx_put_image_to_window(g->mlx, g->win, g->end_img, 0, 0);
}

void	case_check(t_game *g)
{
	int	x;
	int	y;

	x = g->user.x / 64;
	y = g->user.y / 64;
	if ((g->map1)[y][x] == MAP_COLLECTABLE)
		case_eat_collectable(g, x, y);
	if ((g->map1)[y][x] == MAP_EXIT && g->custom.cnt == 0)
		case_enter_escape(g);
}
