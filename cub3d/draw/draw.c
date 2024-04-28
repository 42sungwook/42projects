#include "../srcs/cub3d.h"

void	put_pixel_to_screen(t_data *g, int x, int y, int color)
{
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	g->imgs[SCREEN].addr[y * g->imgs[SCREEN].w + x] = color;
}

void	put_img_to_screen(t_data *g, t_img *imgs, int x, int y)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	if (x > WIDTH - MINI_TILE || y > WIDTH - MINI_TILE || x < 0 || y < 0)
		return ;
	while (i < imgs->h)
	{
		j = 0;
		while (j < imgs->w)
		{
			color = imgs->addr[i * imgs->w + j];
			if (color != 0)
				put_pixel_to_screen(g, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	put_pixel_to_minimap(t_data *g, int x, int y, int color)
{
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	g->imgs[MINI_MAP].addr[y * g->imgs[MINI_MAP].w + x] = color;
}

void	put_img_to_minimap(t_data *g, t_img *imgs, int x, int y)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < imgs->h)
	{
		j = 0;
		while (j < imgs->w)
		{
			color = imgs->addr[i * imgs->w + j];
			if (color != 0)
				put_pixel_to_minimap(g, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	put_minimap_to_screen(t_data *g)
{
	int	x;
	int	y;
	int	i;
	int	j;

	if (g->player->x + P_ERROR < MINI_WIDTH / 2)
		x = 0;
	else if (g->player->x + P_ERROR > g->map_info->w * MINI_TILE - MINI_WIDTH / 2)
		x = g->map_info->w * MINI_TILE - MINI_WIDTH;
	else
		x = g->player->x - MINI_WIDTH / 2;
	if (g->player->y + P_ERROR < MINI_HEIGHT / 2)
		y = 0;
	else if (g->player->y + P_ERROR > g->map_info->h * MINI_TILE - MINI_HEIGHT / 2)
		y = g->map_info->h * MINI_TILE - MINI_HEIGHT;
	else
		y = g->player->y - MINI_HEIGHT / 2;
	i = -1;
	while (++i < MINI_HEIGHT)
	{
		j = -1;
		while (++j < MINI_WIDTH)
			put_pixel_to_screen(g, j, i, g->imgs[MINI_MAP].addr[(y + i) * g->imgs[MINI_MAP].w + x + j]);
	}
}