/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:59:59 by sungwook          #+#    #+#             */
/*   Updated: 2023/01/03 16:00:00 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	init_user_img(t_game *g, void *mlx)
{
	g->user.user_e0 = file_to_image(mlx, "./asset/player_E00.xpm");
	g->user.user_e1 = file_to_image(mlx, "./asset/player_E01.xpm");
	g->user.user_e2 = file_to_image(mlx, "./asset/player_E02.xpm");
	g->user.user_w0 = file_to_image(mlx, "./asset/player_W00.xpm");
	g->user.user_w1 = file_to_image(mlx, "./asset/player_W01.xpm");
	g->user.user_w2 = file_to_image(mlx, "./asset/player_W02.xpm");
	g->user.user_s0 = file_to_image(mlx, "./asset/player_S00.xpm");
	g->user.user_s1 = file_to_image(mlx, "./asset/player_S01.xpm");
	g->user.user_s2 = file_to_image(mlx, "./asset/player_S02.xpm");
	g->user.user_n0 = file_to_image(mlx, "./asset/player_N00.xpm");
	g->user.user_n1 = file_to_image(mlx, "./asset/player_N01.xpm");
	g->user.user_n2 = file_to_image(mlx, "./asset/player_N02.xpm");
}

void	init_custom_img(t_game *g, void *mlx)
{
	int		w;
	int		h;
	char	*path;

	path = "./asset/num_box_16.xpm";
	g->custom.tile0 = mlx_xpm_file_to_image(mlx, "./asset/tile00.xpm", &w, &h);
	g->custom.tile1 = mlx_xpm_file_to_image(mlx, "./asset/tile01.xpm", &w, &h);
	g->custom.ball = mlx_xpm_file_to_image(mlx, "./asset/ball.xpm", &w, &h);
	g->custom.stone = mlx_xpm_file_to_image(mlx, "./asset/stone_t.xpm", &w, &h);
	g->custom.ladder = mlx_xpm_file_to_image(mlx, "./asset/ladder.xpm", &w, &h);
	g->end_img = mlx_xpm_file_to_image(mlx, "./asset/ending.xpm", &w, &h);
	g->game_start = mlx_xpm_file_to_image(mlx, "./asset/opening.xpm", &w, &h);
}
