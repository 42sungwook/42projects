#include "so_long.h"

int	main_loop(t_game *g)
{
	if (g->start == 0 || g->start == 2)
		draw_start(g);
	if (g->reset == 0 && g->start == 1)
	{
		draw_map(g);
		draw_user(g);
		case_check(g);
		if (g->reset == 1)
			return (0);
	}
	return (0);
}

int	press_key(int key_code, t_game *g)
{
	int		x;
	int		y;

	x = g->user.x / 64;
	y = g->user.y / 64;
	if (key_code == KEY_ESC)
		exit(0);
	if ((key_code == 36 && g->start == 0) || (key_code == 36 && g->start == 2))
		g->start = 1;
	else if (g->reset == 1 && key_code == 15)
		game_restart(g);
	else if (g->key_sign && g->start)
		draw_user(g);
	else if (key_code == KEY_D && x < g->map_v.x_size - 1 && !(g->reset))
		draw_move_e(g);
	else if (key_code == KEY_A && x > 0 && !(g->reset))
		draw_move_w(g);
	else if (key_code == KEY_S && y < g->map_v.y_size - 1 && !(g->reset))
		draw_move_s(g);
	else if (key_code == KEY_W && y > 0 && !(g->reset))
		draw_move_n(g);
	return (1);
}

int	close_game(t_game *g)
{
	mlx_destroy_window(g->mlx, g->win);
	exit(0);
}

void	game_start(t_game *game)
{
	int		x_width;
	int		y_width;

	init_start(game, &x_width, &y_width);
	game->mlx = mlx_init();
	init_user_img(game, game->mlx);
	init_custom_img(game, game->mlx);
	game->win = mlx_new_window(game->mlx, x_width, y_width, "42pokemon");
	mlx_hook(game->win, X_EVENT_KEY_PRESS, 0, &press_key, game);
	mlx_hook(game->win, X_EVENT_KEY_EXIT, 0, &close_game, game);
	mlx_loop_hook(game->mlx, &main_loop, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_game	game;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("file error");
		return (0);
	}
	game_init(&game, argv[1]);
	read_map(&game, fd);
	check_valid(&game);
	game_start(&game);
}
