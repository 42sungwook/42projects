/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:43:26 by sungwook          #+#    #+#             */
/*   Updated: 2023/05/29 20:41:44 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_nb_eat_philo(t_data *data, t_philo *philo)
{
	if (data->nb_need_eat != -1 && philo->eat_num >= data->nb_need_eat)
	{
		pthread_mutex_lock(data->eat);
		if (data->nb_end_eat == data->nb_of_philo)
		{
			pthread_mutex_unlock(data->eat);
			return (1);
		}
		pthread_mutex_unlock(data->eat);
	}
	return (0);
}

static int	print_status(t_philo *philo, char *status)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(philo->data->print);
	if (!philo->data->is_dead)
	{
		printf("%ld %d %s\n", ft_get_time() - philo->data->start_time, \
			philo->id + 1, status);
		if (!ft_strcmp(status, "is eating"))
		{
			philo->eat_time = ft_get_time() - philo->data->start_time;
			philo->eat_start = ft_get_time();
		}
	}
	else
		flag = 1;
	pthread_mutex_unlock(philo->data->print);
	if (ft_check_nb_eat_philo(philo->data, philo))
		return (1);
	if (flag)
		return (1);
	return (0);
}

static int	ft_take_fork(t_philo *philo, t_data *data, int i)
{
	pthread_mutex_lock(&data->fork[i]);
	if (print_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(&data->fork[i]);
		return (1);
	}
	pthread_mutex_lock(&data->fork[(i + 1) % data->nb_of_philo]);
	if (print_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(&data->fork[i]);
		pthread_mutex_unlock(&data->fork[(i + 1) % data->nb_of_philo]);
		return (1);
	}
	if (print_status(philo, "is eating"))
	{
		pthread_mutex_unlock(&data->fork[i]);
		pthread_mutex_unlock(&data->fork[(i + 1) % data->nb_of_philo]);
		return (1);
	}
	return (0);
}

static int	ft_routine(t_philo *philo, t_data *data, int i)
{
	if (ft_take_fork(philo, data, i))
		return (1);
	while (ft_get_time() - data->start_time < \
		(philo->eat_time + data->time_to_eat))
		usleep(100);
	philo->eat_num++;
	pthread_mutex_unlock(&data->fork[i]);
	pthread_mutex_unlock(&data->fork[(i + 1) % data->nb_of_philo]);
	if (philo->eat_num == data->nb_need_eat)
	{
		pthread_mutex_lock(data->eat);
		data->nb_end_eat++;
		pthread_mutex_unlock(data->eat);
	}
	if (ft_check_nb_eat_philo(data, philo))
		return (1);
	if (print_status(philo, "is sleeping"))
		return (1);
	while (ft_get_time() - data->start_time < \
		(philo->eat_time + data->time_to_eat + data->time_to_slp))
		usleep(100);
	if (print_status(philo, "is thinking"))
		return (1);
	return (0);
}

void	*ft_thread_function(t_philo *philo)
{
	int		i;
	t_data	*data;

	data = philo->data;
	i = philo->id;
	pthread_mutex_lock(data->init);
	if (data->nb_of_init + 1 == data->nb_of_philo)
		data->start_time = ft_get_time();
	data->nb_of_init++;
	pthread_mutex_unlock(data->init);
	ft_start_mutex(data);
	if (i % 2 == 1)
		usleep(500 * data->time_to_eat);
	while (1)
	{
		if (ft_routine(philo, data, i))
			break ;
	}
	return (NULL);
}
