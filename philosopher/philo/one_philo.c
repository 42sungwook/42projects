/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:55:25 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/30 20:55:26 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_one_philo(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->fork[0]);
	pthread_mutex_lock(data->print);
	philo->eat_start = ft_get_time();
	data->start_time = philo->eat_start;
	printf("%d %d %s\n", 0, philo->id + 1, "has taken a fork");
	pthread_mutex_unlock(data->print);
	while (1)
	{
		pthread_mutex_lock(data->print);
		if (!data->is_dead)
		{
			pthread_mutex_unlock(&data->fork[0]);
			pthread_mutex_unlock(data->print);
			break ;
		}
		pthread_mutex_unlock(data->print);
		usleep(100);
	}
}
