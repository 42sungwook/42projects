/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:31:47 by sungwook          #+#    #+#             */
/*   Updated: 2023/06/01 11:26:54 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_thread_function(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(data->eat);
		if (ft_get_time() - data->eat_start > data->time_to_die)
		{
			sem_wait(data->print);
			printf("%ld %d died\n", ft_get_time() - data->start_time, data->id);
			exit(1);
		}
		if (data->eat_num == data->nb_need_eat)
		{
			sem_wait(data->print);
			exit(0);
		}
		pthread_mutex_unlock(data->eat);
		usleep(100);
	}
}

static void	ft_philo_process(t_data *data)
{
	pthread_t	thread;

	data->start_time = ft_get_time();
	pthread_create(&thread, NULL, (void *)ft_thread_function, (void *)data);
	while (1)
	{
		sem_wait(data->fork);
		if (!sem_wait(data->fork))
		{
			sem_post(data->fork);
			sem_post(data->fork);
		}
		else
		{
			sem_wait(data->print);
			printf("%ld %d has taken a fork\n", ft_get_time() - \
			data->start_time, data->id);
			printf("%ld %d has taken a fork\n", ft_get_time() - \
				data->start_time, data->id);
			printf("%ld %d is eating\n", ft_get_time() - \
				data->start_time, data->id);
			pthread_mutex_lock(data->eat);
			data->eat_num++;
			data->eat_time = ft_get_time() - data->start_time;
			data->eat_start = ft_get_time();
			pthread_mutex_unlock(data->eat);
			sem_post(data->print);
			while (ft_get_time() - data->start_time < data->eat_time + \
				data->time_to_eat)
				usleep(100);
			sem_post(data->fork);
			sem_post(data->fork);
			sem_wait(data->print);
			printf("%ld %d is sleeping\n", ft_get_time() - \
				data->start_time, data->id);
			sem_post(data->print);
			while (ft_get_time() - data->start_time < data->eat_time + \
				data->time_to_eat + data->time_to_slp)
				usleep(100);
			sem_wait(data->print);
			printf("%ld %d is thinking\n", ft_get_time() - \
				data->start_time, data->id);
			sem_post(data->print);
		}
	}
}

int	ft_init_process(t_data *data)
{
	int	i;

	i = 0;
	data->pid = (pid_t *)malloc(sizeof(pid_t) * data->nb_of_philo);
	while (i < data->nb_of_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return (1);
		else if (data->pid[i] == 0)
			ft_philo_process(data);
		i++;
		data->id++;
	}
	return (0);
}
