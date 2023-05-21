#include "philo.h"

int	ft_init_philo(t_data *data, int argc, char **argv)
{
	data->nb_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_slp = ft_atoi(argv[4]);
	data->nb_of_init = 0;
	data->is_dead = 0;
	if (data->nb_of_philo < 1 || data->time_to_die < 0 || \
		data->time_to_eat < 0 || data->time_to_slp < 0)
		return (1);
	data->nb_need_eat = -1;
	if (argc == 6)
	{
		data->nb_need_eat = ft_atoi(argv[5]);
		if (data->nb_need_eat < 0)
			return (1);
	}
	return (0);
}

int	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	data->init = malloc(sizeof(pthread_mutex_t));
	data->print = malloc(sizeof(pthread_mutex_t));
	data->dead = malloc(sizeof(pthread_mutex_t));
	if (!data->fork)
		return (1);
	while (i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(data->init, NULL))
		return (1);
	if (pthread_mutex_init(data->print, NULL))
		return (1);
	if (pthread_mutex_init(data->dead, NULL))
		return (1);
	return (0);
}

int	ft_init_thread(t_data *data, t_philo *philo)
{
	int		i;

	i = 0;
	data->philo = malloc(sizeof(pthread_t) * data->nb_of_philo);
	if (!data->philo)
		return (1);
	data->start_time = ft_get_time();
	while (i < data->nb_of_philo)
	{
		philo[i].data = data;
		philo[i].id = i;
		philo[i].eat_time = 0;
		philo[i].eat_start = ft_get_time();
		if (pthread_create(&data->philo[i], NULL, (void *)ft_routine, philo + i))
			return (1);
		i++;
	}
	return (0);
}
