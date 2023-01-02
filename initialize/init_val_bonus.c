/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_val_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanson <chanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:59:39 by chanson           #+#    #+#             */
/*   Updated: 2023/01/02 16:12:38 by chanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	init_start(t_game *game, int *x_width, int *y_width)
{
	*x_width = game->map_v.x_size * 64;
	*y_width = game->map_v.y_size * 64;
	game->user.x = game->user.pre_x * 64;
	game->user.y = game->user.pre_y * 64;
	game->user.pre_x = game->user.x;
	game->user.pre_y = game->user.y;
	game->user.move = 0;
	game->key_sign = 0;
	game->user.d = 3;
}

void	init_custom(t_custom *new)
{
	new->cnt = 0;
	new->x = 0;
	new->y = 0;
	new->left_ball = 3;
}

void	init_map_v(t_map *new)
{
	new->c = 0;
	new->p = 0;
	new->e = 0;
	new->x_size = 0;
	new->y_size = 0;
	new->total_move = 0;
}

void	game_init(t_game *new, char *argv)
{
	new->mlx = 0;
	new->win = 0;
	new->map = 0;
	new->start = 0;
	new->reset = 0;
	new->addr = argv;
	new->key_sign = 0;
	new->random = 0;
	new->level = 20;
	init_map_v(&(new->map_v));
	init_custom(&(new->custom));
}
