#include "philo.h"

static int	ft_error(t_data *data, char *str)
{
	write(2, str, ft_strlen(str));
	if (data)
	{
		ft_free_data(data);
		free(data);
	}
	return (1);
}

static void	ft_main_thread(t_philo *philo, t_data *data)
{
	int		i;

	i = 0;
	while (1)
	{
		if (ft_monitoring(philo, data))
			break ;
		usleep(100);
	}
	while (i < data->nb_of_philo)
	{
		pthread_join(data->philo_thread[i], NULL);
		i++;
	}
	ft_free_data(data);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	*data;

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
	ft_main_thread(philo, data);
	return (0);
}
