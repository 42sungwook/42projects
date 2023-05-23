#include "philo.h"

long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	print_status(t_philo *philo, char *status)
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

int	monitoring(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_lock(data->print);
		if (philo->eat_start && ft_get_time() - philo->eat_start > data->time_to_die)
		{
			data->is_dead = 1;
			printf("%ld %d is dead\n", ft_get_time() - data->start_time, philo->id + 1);
			pthread_mutex_unlock(data->print);
			return (1);
		}
		pthread_mutex_unlock(data->print);
		philo++;
		i++;
	}
	return (0);
}

void	ft_free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->fork)
	{
		while (i < data->nb_of_philo)
		{
			pthread_mutex_destroy(&data->fork[i]);
			i++;
		}
		free(data->fork);
	}
	if (data->philo)
		free(data->philo);
	if (data->init)
	{
		pthread_mutex_destroy(data->init);
		free(data->init);
	}
	if (data->print)
	{
		pthread_mutex_destroy(data->print);
		free(data->print);
	}
	if (data->dead)
	{
		pthread_mutex_destroy(data->dead);
		free(data->dead);
	}
	if (data)
		free(data);
}

int	ft_error(t_data *data, char *str)
{
	write(2, str, ft_strlen(str));
	if (data)
	{
		ft_free_data(data);
		free(data);
	}
	return (1);
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
	while (1)
	{
		pthread_mutex_lock(data->init);
		if (data->nb_of_init == data->nb_of_philo)
		{
			pthread_mutex_unlock(data->init);
			break ;
		}
		pthread_mutex_unlock(data->init);
	}
	if (i % 2 == 1)
		usleep(500 * data->time_to_eat);
	while (1)
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
	}
	return (NULL);
}


int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	if (!(argc == 5 || argc == 6))
		return (ft_error(data, "Error: Invalid Arguments\n"));
	if (!data)
		return (1);
	if (ft_init_philo(data, argc, argv))
		return (ft_error(data, "Error: Invalid Argument Number\n"));
	if (ft_init_mutex(data))
		return (ft_error(data, "Error: Mutex Init Error\n"));
	philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (ft_init_thread(data, philo))
		return (ft_error(data, "Error: Thread Init Error\n"));
	while (1)
	{
		if (monitoring(philo, data))
			break ;
		usleep(100);
	}
	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_join(data->philo[i], NULL);
		i++;
	}
	ft_free_data(data);
	free(philo);
	return (0);
}
