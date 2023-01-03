/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:00:08 by chanson           #+#    #+#             */
/*   Updated: 2023/01/03 15:47:09 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	draw_left_ball_count(t_game *g)
{
	char	*str;

	str = NULL;
	str = ft_itoa(g->custom.left_ball);
	mlx_put_image_to_window(g->mlx, g->win, g->custom.n_box, 64, 0);
	mlx_string_put(g->mlx, g->win, 93, 35, 0x23652f, str);
	free(str);
}

void	draw_step_count(t_game *g)
{
	char	*str;

	str = NULL;
	str = ft_itoa(g->user.move);
	mlx_put_image_to_window(g->mlx, g->win, g->custom.n_box, 0, 0);
	mlx_string_put(g->mlx, g->win, 30, 35, 0x000000, str);
	free(str);
}

void	draw_start(t_game *g)
{
	static int	random;
	char		*line;
	char		*instruction;
	char		*instruction2;

	line = "Press enter!!";
	instruction = "WASD to move";
	instruction2 = "K to catch";
	g->random = random;
	mlx_clear_window(g->mlx, g->win);
	if (g->start == 0)
	{
		mlx_put_image_to_window(g->mlx, g->win, g->game_start, 0, 0);
		mlx_string_put(g->mlx, g->win, 500, 64, 0xFFFFFF, line);
		mlx_string_put(g->mlx, g->win, 500, 128, 0xFFFFFF, instruction);
		mlx_string_put(g->mlx, g->win, 500, 192, 0xFFFFFF, instruction2);
	}
	else
	{
		line = "Press enter to start the next step";
		mlx_string_put(g->mlx, g->win, 500, 64, 0xFFFFFF, line);
	}
	random++;
}

void static	_draw_map(t_game *g, int cha, int x, int y)
{
	void	*mlx;
	void	*win;

	mlx = g->mlx;
	win = g->win;
	if (cha == MAP_WALL)
		mlx_put_image_to_window(mlx, win, g->custom.tile1, x * 64, y * 64);
	else if (cha == MAP_BLACK || cha == MAP_USER)
		mlx_put_image_to_window(mlx, win, g->custom.tile0, x * 64, y * 64);
	else if (cha == MAP_COLLECTABLE)
	{
		mlx_put_image_to_window(mlx, win, g->custom.tile0, x * 64, y * 64);
		mlx_put_image_to_window(mlx, win, g->custom.ball, x * 64, y * 64);
	}
	else if (cha == MAP_EXIT && g->custom.cnt != 0)
		mlx_put_image_to_window(mlx, win, g->custom.stone, x * 64, y * 64);
	else if (cha == MAP_EXIT && g->custom.cnt == 0)
		mlx_put_image_to_window(mlx, win, g->custom.ladder, x * 64, y * 64);
}

void	draw_map(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	mlx_clear_window(g->mlx, g->win);
	while (y < g->map_v.y_size)
	{
		x = 0;
		while (x < g->map_v.x_size)
		{
			if ((g->map1)[y][x] == MAP_WALL)
				_draw_map(g, MAP_WALL, x, y);
			else if ((g->map1)[y][x] == MAP_COLLECTABLE)
				_draw_map(g, MAP_COLLECTABLE, x, y);
			else if ((g->map1)[y][x] == MAP_EXIT)
				_draw_map(g, MAP_EXIT, x, y);
			else if ((g->map1)[y][x] == MAP_USER)
				_draw_map(g, MAP_USER, x, y);
			else
				_draw_map(g, MAP_BLACK, x, y);
			x++;
		}
		y++;
	}
}
