#include "../srcs/cub3d.h"

void draw_minimap(t_data *g)
{
	int i;
	int j;
	int tile_x;
	int tile_y;
	int tile_color;

	i = 0;
	while (g->map_info->map[i])
	{
		j = 0;
		while (g->map_info->map[i][j])
		{
			if (g->map_info->map[i][j] == '1')
				put_img_to_screen(g, &g->imgs[1], j * TILE_SIZE, i * TILE_SIZE);
			else
				put_img_to_screen(g, &g->imgs[4], j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
}



//플레이어 주변맵을 확인
//주변 기준으로 끝이 나온다면 처리-> 그냥 맵의 앞부분부터 그려야함