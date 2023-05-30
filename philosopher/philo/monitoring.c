/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:43:23 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/30 20:52:29 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_nb_eat_main(t_data *data)
{
	pthread_mutex_lock(data->eat);
	if (data->nb_end_eat == data->nb_of_philo)
	{
		pthread_mutex_unlock(data->eat);
		return (1);
	}
	pthread_mutex_unlock(data->eat);
	return (0);
}

int	ft_monitoring(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (data->nb_need_eat > 0 && ft_check_nb_eat_main(data))
			return (1);
		pthread_mutex_lock(data->print);
		if (philo->eat_start && ft_get_time() - \
			philo->eat_start > data->time_to_die)
		{
			data->is_dead = 1;
			printf("%ld %d is dead\n", ft_get_time() - \
			data->start_time, philo->id + 1);
			pthread_mutex_unlock(data->print);
			return (1);
		}
		pthread_mutex_unlock(data->print);
		philo++;
		i++;
	}
	return (0);
}
