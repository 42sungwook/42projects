#include "philo.h"

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
	if (flag)
		return (1);
	return (0);
}

void	*ft_routine(t_philo *philo)
{
	int		i;
	int		eat_num;
	t_data	*data;

	eat_num = 0;
	data = philo->data;
	i = philo->id;
	pthread_mutex_lock(data->init);
	if (data->nb_of_init + 1 == data->nb_of_philo)
		data->start_time = ft_get_time();
	data->nb_of_init++;
	pthread_mutex_unlock(data->init);
	ft_start_mutex(data);
	while (1)
	{
		if (i % 2 == 1)
		{
			pthread_mutex_lock(&data->fork[i]);
			if (print_status(philo, "has taken a fork"))
			{
				pthread_mutex_unlock(&data->fork[i]);
				break ;
			}
			pthread_mutex_lock(&data->fork[(i + 1) % data->nb_of_philo]);
			if (print_status(philo, "has taken a fork"))
			{
				pthread_mutex_unlock(&data->fork[i]);
				pthread_mutex_unlock(&data->fork[(i + 1) % data->nb_of_philo]);
				break ;
			}
		}
		else
		{
            usleep(10);
			pthread_mutex_lock(&data->fork[(i + 1) % data->nb_of_philo]);
			if (print_status(philo, "has taken a fork"))
			{
				pthread_mutex_unlock(&data->fork[(i + 1) % data->nb_of_philo]);
				break ;
			}
			pthread_mutex_lock(&data->fork[i]);
			if (print_status(philo, "has taken a fork"))
			{
				pthread_mutex_unlock(&data->fork[i]);
				pthread_mutex_unlock(&data->fork[(i + 1) % data->nb_of_philo]);
				break ;
			}
		}
		if (print_status(philo, "is eating"))
		{
			pthread_mutex_unlock(&data->fork[i]);
			pthread_mutex_unlock(&data->fork[(i + 1) % data->nb_of_philo]);
			break ;
		}
		while (ft_get_time() - data->start_time < (philo->eat_time + data->time_to_eat))
			usleep(100);
		eat_num++;
		pthread_mutex_unlock(&data->fork[i]);
		pthread_mutex_unlock(&data->fork[(i + 1) % data->nb_of_philo]);
		if (print_status(philo, "is sleeping"))
			break ;
		if (eat_num == data->nb_need_eat)
			break ;
		while (ft_get_time() - data->start_time < (philo->eat_time + data->time_to_eat + data->time_to_slp))
			usleep(100);
		if (print_status(philo, "is thinking"))
			break ;
	}
	return (NULL);
}
