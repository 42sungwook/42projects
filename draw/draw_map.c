#include "../so_long.h"

void	draw_start(t_game *g)
{
	char		*line;
	char		*instruction;

	line = "Press enter!!";
	instruction = "WASD to move";
	mlx_clear_window(g->mlx, g->win);
	if (g->start == 0)
	{
		mlx_put_image_to_window(g->mlx, g->win, g->game_start, 0, 0);
		mlx_string_put(g->mlx, g->win, 500, 64, 0xFFFFFF, line);
		mlx_string_put(g->mlx, g->win, 500, 128, 0xFFFFFF, instruction);
	}
	else
	{
		line = "Press enter to start the next step";
		mlx_string_put(g->mlx, g->win, 500, 64, 0xFFFFFF, line);
	}
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
