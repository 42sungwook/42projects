/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:31:47 by sungwook          #+#    #+#             */
/*   Updated: 2023/06/02 23:09:13 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_print_status(t_data *data, char *str)
{
	sem_wait(data->print);
	printf("%ld %d %s\n", ft_get_time() - data->start_time, data->id, str);
	sem_post(data->print);
}

static void	ft_check_philo_death(t_data *data)
{
	if (data->nb_need_eat > 0 && data->eat_num == data->nb_need_eat)
	{
		sem_wait(data->print);
		exit(0);
	}
	if (data->eat_start && ft_get_time() - data->eat_start > data->time_to_die)
	{
		sem_wait(data->print);
		printf("%ld %d died\n", ft_get_time() - data->start_time, data->id);
		exit(1);
	}
}

static void	ft_philo_process(t_data *data)
{
	int			i;

	sem_wait(data->init);
	sem_post(data->init);
	data->start_time = ft_get_time();
	if (data->id % 2 == 0)
		usleep(500 * data->time_to_eat);
	while (1)
	{
		ft_check_philo_death(data);
		sem_wait(data->fork);
		ft_print_status(data, "has taken a fork");
		sem_wait(data->fork);
		ft_check_philo_death(data);
		ft_print_status(data, "has taken a fork");
		ft_check_philo_death(data);
		ft_print_status(data, "is eating");
		data->eat_num++;
		data->eat_start = ft_get_time();
		i = -1;
		while (++i < data->time_to_eat * 10)
		{
			ft_check_philo_death(data);
			usleep(100);
		}
		sem_post(data->fork);
		sem_post(data->fork);
		ft_check_philo_death(data);
		ft_print_status(data, "is sleeping");
		i = -1;
		while (++i < data->time_to_slp * 10)
		{
			ft_check_philo_death(data);
			usleep(100);
		}
		ft_check_philo_death(data);
		ft_print_status(data, "is thinking");
	}
}

int	ft_init_process(t_data *data)
{
	int	i;

	data->pid = (pid_t *)malloc(sizeof(pid_t) * data->nb_of_philo);
	data->start_time = ft_get_time();
	i = -1;
	while (++i < data->nb_of_philo)
		sem_wait(data->init);
	i = -1;
	while (++i < data->nb_of_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return (1);
		else if (data->pid[i] == 0)
		{
			data->id = i + 1;
			ft_philo_process(data);
		}
	}
	i = -1;
	data->start_time = ft_get_time();
	while (++i < data->nb_of_philo)
		sem_post(data->init);
	return (0);
}
