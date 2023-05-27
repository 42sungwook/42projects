#include "philo.h"

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
	if (data->philo_thread)
		free(data->philo_thread);
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