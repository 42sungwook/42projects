/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:01:10 by sungwook          #+#    #+#             */
/*   Updated: 2023/01/03 16:01:11 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_free(int **arr, t_game *g)
{
	int	j;

	j = 0;
	if (!arr)
		return ;
	while (j < g->map_v.y_size)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

int	**make_int_map(t_game *g, size_t i, size_t j)
{
	int	**arr;

	arr = (int **)malloc(sizeof(int *) * (g->map_v.y_size));
	while ((g->map)[i])
	{
		arr[i] = (int *)malloc(sizeof(int) * (g->map_v.x_size));
		j = 0;
		while ((g->map)[i][j] != '\n' && (g->map)[i][j] != 0)
		{
			if ((g->map)[i][j] == '0')
				arr[i][j] = 0;
			else if ((g->map)[i][j] == 'C')
				arr[i][j] = -2;
			else if ((g->map)[i][j] == 'E')
				arr[i][j] = -3;
			else if ((g->map)[i][j] == 'P')
				arr[i][j] = -4;
			else if ((g->map)[i][j] == '1')
				arr[i][j] = -1;
			j++;
		}
		i++;
	}
	return (arr);
}

int	**dup_arr(int **arr, int size_x, int size_y)
{
	int	x;
	int	y;
	int	**arr2;

	y = 0;
	arr2 = (int **)malloc(sizeof(int *) * size_y);
	while (y < size_y)
	{
		x = 0;
		arr2[y] = (int *)malloc(sizeof(int *) * size_x);
		while (x < size_x)
		{
			arr2[y][x] = arr[y][x];
			x++;
		}
		y++;
	}
	return (arr2);
}

void	print_user_move(t_game *g)
{
	char	*move_count;
	size_t	i;

	i = 0;
	move_count = ft_itoa(g->user.move);
	while (move_count[i])
		i++;
	write(1, move_count, i);
	write(1, "\n", 1);
	free(move_count);
}
