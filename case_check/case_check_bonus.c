/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_check_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanson <chanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:00:37 by chanson           #+#    #+#             */
/*   Updated: 2023/01/02 21:50:52 by chanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	game_next_start(t_game *g)
{
	int	fd;

	mlx_destroy_window(g->mlx, g->win);
	g->addr = "./maps/map2.ber";
	ft_free(g->map1, g);
	ft_free(g->map2, g);
	fd = open(g->addr, O_RDONLY);
	if (fd == -1)
	{
		perror("file error");
		exit(0);
	}
	game_init(g, g->addr);
	read_map(g);
	check_valid(g);
	g->start = 2;
	game_start(g);
}

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
	g->custom.left_ball = 3;
	init_enemy(g);
	g->start = 0;
	return (0);
}

void	case_eat_collectable(t_game *g, int x, int y)
{
	g->map_v.total_move += 3;
	g->custom.cnt--;
	g->custom.left_ball++;
	(g->map1)[y][x] = 0;
}

void	case_enter_escape(t_game *g)
{
	mlx_clear_window(g->mlx, g->win);
	g->key_sign = 0;
	g->reset = 1;
	if (g->enemy_list)
		delete_complete_deque(g->enemy_list, g);
	if (check_str(g->addr, "map1"))
	{
		ft_free2(g->map);
		game_next_start(g);
	}
	else
		mlx_put_image_to_window(g->mlx, g->win, g->end_img, 0, 0);
}

void	case_check(t_game *g)
{
	int	x;
	int	y;

	x = g->user.x / 64;
	y = g->user.y / 64;
	if ((g->map1)[y][x] == -2)
		case_eat_collectable(g, x, y);
	if ((g->map1)[y][x] == -3 && g->custom.cnt == 0)
		case_enter_escape(g);
	if (player_meet_enemy(g))
		put_game_over_img(g);
}
