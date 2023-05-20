#include "philo.h"

int	print_error(t_data *data, char *str)
{
	write(2, str, ft_strlen(str));
	if (data)
		ft_free_data(data);
	return (1);
}

long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_init_philo(t_data *data, int argc, char **argv)
{
	t_data	*data;

	data->nb_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_slp = ft_atoi(argv[4]);
	if (data->nb_of_philo < 1 || data->time_to_die < 0 || \
		data->time_to_eat < 0 || data->time_to_slp < 0)
		return (1);
	data->nb_eat = -1;
	if (argc == 6)
	{
		data->nb_eat = ft_atoi(argv[5]);
		if (data->nb_eat < 0)
			return (1);
	}
	return (0);
}

int	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->fork)
		return (1);
	while (i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL))
		return (1);
	if (pthread_mutex_init(&data->dead, NULL))
		return (1);
	if (pthread_mutex_init(&data->eat, NULL))
		return (1);
	return (0);
}

int	ft_routine(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (pthread_mutex_lock(&data->fork[i]))
			return (1);
		if (pthread_mutex_lock(&data->fork[(i + 1) % data->nb_of_philo]))
			return (1);
		if (ft_eat(data, i))
			return (1);
		if (pthread_mutex_unlock(&data->fork[i]))
			return (1);
		if (pthread_mutex_unlock(&data->fork[(i + 1) % data->nb_of_philo]))
			return (1);
		if (ft_sleep(data, i))
			return (1);
		if (ft_think(data, i))
			return (1);
	}
	return (0);
}

int	ft_init_thread(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(pthread_t) * data->nb_of_philo);
	if (!data->philo)
		return (1);
	data->start_time = ft_get_time();
	while (i < data->nb_of_philo)
	{
		if (pthread_create(&data->philo[i], NULL, ft_routine, &data->philo[i]))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!(argc == 5 || argc == 6))
		return (print_error("Error: Invalid Arguments\n"));
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (ft_init_philo(data, argc, argv))
		return (ft_error("Error: Invalid Argument Number\n"));
	if (ft_init_mutex(data))
		return (ft_error("Error: Mutex Init Error\n"));
	if (ft_init_thread(data))
		return (ft_error("Error: Thread Init Error\n"));
	ft_wait_thread(data);
	ft_free_philo(data);
	return (0);
}
