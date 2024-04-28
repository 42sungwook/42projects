#include "../srcs/cub3d.h"

void draw_miniplayer(t_data *g)
{
	int	new_x;
	int	new_y;

	if (g->player->turn_dir != 0)
	{
		g->player->rotation_angle += g->player->turn_dir * (PI / 180.0) * ROT_SPEED;
	}
	new_x = g->player->x + (int)(cos(g->player->rotation_angle + (PI / 180.0) * 90.0 * g->player->walk_dir) * MOVE_SPEED);
	new_y = g->player->y + (int)(sin(g->player->rotation_angle + (PI / 180.0) * 90.0 * g->player->walk_dir) * MOVE_SPEED);

	if (g->player->walk_dir != STOP && !is_wall(g, new_x, new_y))
	{
		g->player->x = new_x;
		g->player->y = new_y;
	}
	put_img_to_minimap(g, &g->imgs[MINI_PLAYER], g->player->x, g->player->y);
}
