/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:01:07 by sungwook          #+#    #+#             */
/*   Updated: 2023/01/03 16:01:08 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	ft_free2(char **arr)
{
	int	j;

	j = 0;
	if (!arr)
		return ;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr[j]);
	free(arr);
}

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
			if ((g->map)[i][j] >= '0' && \
				(g->map)[i][j] < '9' && (g->map)[i][j] != '1')
				arr[i][j] = (g->map)[i][j] - '0';
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

int	check_str(char *str1, char *str2)
{
	int		i;
	int		j;
	int		sign;

	i = -1;
	while (str1[++i])
	{
		if (str1[i] == str2[0])
		{
			j = 0;
			sign = 0;
			while (str1[i + j] && str2[j])
			{
				if (str1[i + j] == str2[j])
					sign = 1;
				else
					sign = 0;
				j++;
			}
			if (str2[j] == '\0' && sign == 1)
				return (1);
		}
	}
	return (0);
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
