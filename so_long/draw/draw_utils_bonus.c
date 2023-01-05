/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:59:34 by sungwook          #+#    #+#             */
/*   Updated: 2023/01/03 15:59:36 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	put_image_to_window(t_game *g, int x, int y, void *image)
{
	mlx_put_image_to_window(g->mlx, g->win, image, x, y);
}

void	*file_to_image(void *mlx, char *addr)
{
	int		w;
	int		h;
	void	*result;

	result = mlx_xpm_file_to_image(mlx, addr, &w, &h);
	return (result);
}
