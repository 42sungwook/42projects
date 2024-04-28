/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_check2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:58:31 by sungwook          #+#    #+#             */
/*   Updated: 2023/01/03 15:58:34 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

int	player_meet_enemy(t_game *g)
{
	t_node	*temp;
	int		x;
	int		y;

	x = g->user.x / 64;
	y = g->user.y / 64;
	temp = g->enemy_list->front;
	while (temp)
	{
		if ((temp->enemy_alive == 1) && (temp->x == x) && (temp->y == y))
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	put_game_end_img(t_game *g)
{
	mlx_clear_window(g->mlx, g->win);
	g->key_sign = 0;
	g->reset = 1;
	mlx_put_image_to_window(g->mlx, g->win, g->end_img, 0, 0);
}

void	put_game_over_img(t_game *g)
{
	if (g->enemy_list)
		delete_complete_deque(g->enemy_list, g);
	mlx_clear_window(g->mlx, g->win);
	g->key_sign = 0;
	g->reset = 1;
	mlx_put_image_to_window(g->mlx, g->win, g->game_over, 0, 0);
}

void	find_site(int **arr, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	game->custom.cnt = 0;
	while (y < game->map_v.y_size)
	{
		x = -1;
		while (x++ < game->map_v.x_size - 1)
		{
			if (arr[y][x] == -3)
			{
				game->custom.x = x;
				game->custom.y = y;
			}
			else if (arr[y][x] == -4)
			{
				game->user.x = x;
				game->user.y = y;
			}
			if (arr[y][x] == -2)
				game->custom.cnt++;
		}
		y++;
	}
}

void	catch_enemy(t_game *g)
{
	t_node	*temp;
	int		x;
	int		y;

	temp = g->enemy_list->front;
	x = g->user.x / 64;
	y = g->user.y / 64;
	g->custom.left_ball--;
	while (temp)
	{
		if (temp->enemy_alive == 1)
		{
			if ((temp->x == x + 1) && (temp->y == y))
				temp->enemy_alive = 2;
			else if ((temp->x == x - 1) && (temp->y == y))
				temp->enemy_alive = 2;
			else if ((temp->x == x) && (temp->y == y + 1))
				temp->enemy_alive = 2;
			else if ((temp->x == x) && (temp->y == y - 1))
				temp->enemy_alive = 2;
		}
		temp = temp->next;
	}
}
