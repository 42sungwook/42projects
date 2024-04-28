/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:32:42 by sungwook          #+#    #+#             */
/*   Updated: 2023/06/03 16:37:42 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_one_philo_process(t_data *data)
{
	data->pid = (pid_t *)malloc(sizeof(pid_t));
	data->pid[0] = fork();
	if (data->pid[0] < 0)
	{
		write(2, "Error: Process Init Error\n", 26);
		exit(1);
	}
	else if (data->pid[0] == 0)
	{
		data->start_time = ft_get_time();
		printf("%ld %d %s\n", ft_get_time() - data->start_time, \
				1, "has taken a fork");
		while (1)
		{
			if (ft_get_time() - data->start_time > data->time_to_die)
			{
				printf("%ld %d is dead\n", ft_get_time() - data->start_time, 1);
				break ;
			}
			usleep(100);
		}
		exit(0);
	}
}
